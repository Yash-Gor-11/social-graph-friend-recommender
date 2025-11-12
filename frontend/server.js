// server.js
import express from 'express';
import fs from 'fs';
import { execFile } from 'child_process';
import path from 'path';

const app = express();
const PORT = 5000;

// ======= UPDATE THESE PATHS (they are absolute) =======
const CSV_PATH = path.resolve(
  "C:/Users/yashg/OneDrive/Desktop/DSA_PROJECT/social-graph-friend-recommender/backend/dataset/users.csv"
);

const BACKEND_PATH = path.resolve(
  "C:/Users/yashg/OneDrive/Desktop/DSA_PROJECT/social-graph-friend-recommender/backend/build/social_graph_app.exe"
);

// Backend working directory (where exe expects to find dataset/)
const BACKEND_DIR = path.resolve(
  "C:/Users/yashg/OneDrive/Desktop/DSA_PROJECT/social-graph-friend-recommender/backend"
);

// =====================================================

app.use(express.json());
app.use(express.static('./')); // serve index.html, style.css, script.js

// Helper to read usernames from CSV (for /users route)
// Format: id,username,friends
function readCSVIntoArray(csvPath) {
  return new Promise((resolve, reject) => {
    const users = new Set();
    if (!fs.existsSync(csvPath)) return resolve([]);
    fs.createReadStream(csvPath)
      .on('data', chunk => {
        const lines = chunk.toString().split('\n');
        lines.forEach(line => {
          line = line.trim();
          if (!line) return;
          const parts = line.split(',');
          if (parts.length >= 2) {
            const username = parts[1].trim();
            if (username) users.add(username);
          }
        });
      })
      .on('end', () => resolve(Array.from(users)))
      .on('error', reject);
  });
}

// GET /users -> returns list of usernames
app.get('/users', async (req, res) => {
  try {
    const users = await readCSVIntoArray(CSV_PATH);
    res.json(users);
  } catch (e) {
    res.status(500).json({ error: String(e) });
  }
});

// Generic exec helper that ensures correct working directory
function runBackend(args, cb) {
  execFile(
    BACKEND_PATH,
    args,
    { cwd: BACKEND_DIR, timeout: 10_000 }, // 👈 critical fix
    (err, stdout, stderr) => {
      // If we have stdout, use it regardless of exit code
      if (stdout) return cb(null, stdout.trim());
      // Otherwise, if there's an error, pass stderr or error message
      if (err) return cb(stderr || err.message);
      // Fallback to stderr if no stdout
      cb(null, (stderr || '').trim());
    }
  );
}

// ========== API ENDPOINTS MAPPED TO CLI FEATURES ==========

// Add user
app.post('/add', (req, res) => {
  const username = req.body.username;
  runBackend(['--add', username], (err, out) => res.json({ output: err ? err : out }));
});

// Remove user
app.post('/remove', (req, res) => {
  const username = req.body.username;
  runBackend(['--remove', username], (err, out) => res.json({ output: err ? err : out }));
});

// Add friendship
app.post('/addFriend', (req, res) => {
  const { a, b } = req.body;
  runBackend(['--addFriend', a, b], (err, out) => res.json({ output: err ? err : out }));
});

// Remove friendship
app.post('/removeFriend', (req, res) => {
  const { a, b } = req.body;
  runBackend(['--removeFriend', a, b], (err, out) => res.json({ output: err ? err : out }));
});

// Clear graph
app.post('/clear', (req, res) => {
  runBackend(['--clear'], (err, out) => res.json({ output: err ? err : out }));
});

// Get friends of a user
app.get('/friends', (req, res) => {
  const q = req.query.q || '';
  runBackend(['--friends', q], (err, out) => res.json({ output: err ? err : out }));
});

// Mutual friends
app.get('/mutual', (req, res) => {
  const a = req.query.a || '';
  const b = req.query.b || '';
  runBackend(['--mutual', a, b], (err, out) => res.json({ output: err ? err : out }));
});

// Connection check (BFS)
app.get('/connection', (req, res) => {
  const a = req.query.a || '';
  const b = req.query.b || '';
  runBackend(['--connection', a, b], (err, out) => res.json({ output: err ? err : out }));
});

// PageRank
app.get('/pagerank', (req, res) => {
  const q = req.query.q || '';
  runBackend(['--pagerank', q], (err, out) => res.json({ output: err ? err : out }));
});

// Recommend friends
app.get('/recommend', (req, res) => {
  const q = req.query.q || '';
  runBackend(['--recommend', q], (err, out) => res.json({ output: err ? err : out }));
});

// Search usernames
app.get('/search', (req, res) => {
  const q = req.query.q || '';
  if (!q) return res.json([]);
  runBackend(['--search', q], (err, out) => {
    if (err) return res.json([]);
    const arr = out.split(',').filter(Boolean);
    res.json(arr);
  });
});

// Exit (optional)
app.post('/exit', (req, res) => {
  runBackend(['--exit'], (err, out) => res.json({ output: err ? err : out }));
});

app.listen(PORT, () => console.log(`✅ Server running at http://localhost:${PORT}`));