# 🌐 Social Graph Friend Recommender

A full-stack social network engine combining **C++ graph algorithms**, **real-time autocomplete search**, and a **modern interactive web interface**. Intelligently recommends friends using PageRank and mutual connection analysis.

**Live Demo**: Start the server and visit `http://localhost:5000`

---

## 📋 Table of Contents

1. [Features](#-features)
2. [Tech Stack](#-tech-stack)
3. [Project Structure](#-project-structure)
4. [Quick Start](#-quick-start)
5. [Usage Guide](#-usage-guide)
6. [API Reference](#-api-reference)
7. [Architecture](#-architecture)
8. [Data Format](#-data-format)
9. [Performance](#-performance)
10. [Troubleshooting](#-troubleshooting)

---

## ✨ Features

### Backend (C++)
- ✅ **User Management** - Add/remove users with deterministic hash IDs
- ✅ **Bidirectional Friendships** - Adjacency list graph structure
- ✅ **Smart Recommendations** - Score-based algorithm using mutual friends + PageRank
- ✅ **Connection Detection** - BFS pathfinding between any two users
- ✅ **Prefix Search** - O(k) Trie-based autocomplete search
- ✅ **PageRank Scoring** - Calculate influence scores for all users
- ✅ **Persistent Storage** - CSV-based data with automatic two-pass loading
- ✅ **CLI & API Modes** - Interactive menu + command-line arguments
- ✅ **Silent Mode** - Output suppression for server integration

### Frontend (Web)
- ✅ **Beautiful UI** - Glassmorphic design with animated particle background
- ✅ **Real-time Search** - Autocomplete suggestions as you type
- ✅ **Organized Sections** - Logical grouping of features
- ✅ **Desktop-optimized, Single-column Layout** - Primary design targets desktop; internal panels may scroll when content overflows
- ✅ **Live Console** - Real-time output of all operations
- ✅ **Modern Animations** - Smooth transitions and pulsing particles
- ✅ **Error Handling** - User-friendly validation and error messages

---

## 🛠️ Tech Stack

| Component | Technology | Details |
|-----------|-----------|---------|
| **Backend** | C++23 | Graph algorithms, Trie search, PageRank |
| **Server** | Node.js + Express | RESTful API gateway |
| **Frontend** | Vanilla JavaScript | No frameworks, pure ES6 modules |
| **Styling** | CSS3 | Glassmorphic design, custom animations |
| **Data** | CSV | Persistent user storage |
| **Build** | Make | Automated compilation with MSYS2 g++ |

---

## 📁 Project Structure

```
social-graph-friend-recommender/
├── README.md                          # This file
│
├── backend/                           # C++ Application
│   ├── README.md                      # Backend documentation
│   ├── Makefile                       # Build configuration
│   ├── src/
│   │   ├── main.cpp                  # Entry point, CLI interface
│   │   ├── graph/
│   │   │   ├── Graph.hpp             # Graph class definition
│   │   │   └── Graph.cpp             # Graph implementation
│   │   ├── io/
│   │   │   ├── FileManager.hpp       # CSV I/O interface
│   │   │   └── FileManager.cpp       # Two-pass CSV loader/saver
│   │   ├── search/
│   │   │   ├── Trie.hpp              # Trie definition
│   │   │   └── Trie.cpp              # Trie implementation
│   │   └── utils/
│   │       ├── Utils.hpp             # Utility interface
│   │       └── Utils.cpp             # Hash ID generation
│   ├── dataset/
│   │   └── users.csv                 # Main dataset (id,username,friends)
│   └── build/                         # Compiled output
│
└── frontend/                          # Web Interface
    ├── index.html                     # HTML structure
    ├── style.css                      # Styling & animations
    ├── background.js                  # Particle animation
    ├── script.js                      # Main logic & API calls
    ├── server.js                      # Express.js server
    ├── package.json                   # Dependencies
    └── js/                            # (Optional) Modular JS modules
```

---

## 🚀 Quick Start

### Prerequisites
- **Windows**: [MSYS2](https://www.msys2.org/) with MinGW64
- **Node.js**: v14 or higher
- **Port 5000**: Must be available

### Step 1: Build Backend
```bash
cd backend
make
```
Expected output: `✅ Build successful!` and `social_graph_app.exe` in `build/`

### Step 2: Install Frontend Dependencies
```bash
cd ../frontend
npm install
```

### Step 3: Start Server
```bash
npm start
# or
node server.js
```
Expected: `✅ Server running at http://localhost:5000`

### Step 4: Open Browser
```
http://localhost:5000
```

---

## 📖 Usage Guide

### Adding Users
1. Enter username in the **User Management** section
2. Click **Add User**
3. User appears in "Display All Users" and search suggestions

### Creating Friendships
1. Enter two usernames in the **Friendship** section
2. Click **Add** to create bidirectional friendship
3. Click **Remove** to delete friendship

### Searching for Users
1. Type in the **Search Users** box
2. Autocomplete suggestions appear below
3. Click suggestion to select and log it

### Getting Friend Info
1. Enter username in **User Analysis** section
2. Click **Friends** to see all friends
3. Click **PageRank** to see influence score

### Finding Mutual Friends
1. Enter two usernames in **Mutual Friends** section
2. Click **Find Mutual** to see common friends

### Checking Connections
1. Enter two usernames in **Connection Check** section
2. Click **Check Path** to verify if connected
3. Returns "Connected: Yes" or "Connected: No"

### Getting Recommendations
1. Enter username in **Recommendations** section
2. Click **Get Recommendations** to see suggested friends
3. Suggestions based on mutual friends + PageRank influence

### Utility Operations
- **Display All Users** - List all users in console
- **Clear Graph** - Remove all data (confirmation required)

---

## 🔌 API Reference

All endpoints respond with JSON format: `{ "output": "result text" }`

### GET Endpoints

| Endpoint | Parameters | Example | Description |
|----------|-----------|---------|-------------|
| `/users` | - | `/users` | Get all usernames |
| `/friends` | `q=username` | `/friends?q=alice` | Get friends of user |
| `/mutual` | `a=user1&b=user2` | `/mutual?a=alice&b=bob` | Get mutual friends |
| `/connection` | `a=user1&b=user2` | `/connection?a=alice&b=bob` | Check if connected |
| `/pagerank` | `q=username` | `/pagerank?q=alice` | Get PageRank score |
| `/recommend` | `q=username` | `/recommend?q=alice` | Get recommendations |
| `/search` | `q=prefix` | `/search?q=al` | Search by prefix |

### POST Endpoints

| Endpoint | Body | Example | Description |
|----------|------|---------|-------------|
| `/add` | `{username}` | `{"username":"alice"}` | Add user |
| `/remove` | `{username}` | `{"username":"alice"}` | Remove user |
| `/addFriend` | `{a,b}` | `{"a":"alice","b":"bob"}` | Create friendship |
| `/removeFriend` | `{a,b}` | `{"a":"alice","b":"bob"}` | Delete friendship |
| `/clear` | `{}` | `{}` | Clear all data |

### Example cURL Commands

```bash
# Add a user
curl -X POST http://localhost:5000/add \
  -H "Content-Type: application/json" \
  -d '{"username":"alice"}'

# Get friends
curl http://localhost:5000/friends?q=alice

# Get recommendations
curl http://localhost:5000/recommend?q=alice
```

---

## 🏗️ Architecture

### Data Flow

```
User Input
    ↓
[HTML Form] → [JavaScript Handler]
    ↓
[Fetch API] → [Express Server]
    ↓
[C++ Backend] → [Graph Algorithm]
    ↓
[CSV Storage] → [FileManager]
    ↓
[JSON Response] → [Console Output]
```

### Key Components

**Graph (C++)**
- Adjacency list with `unordered_map<string, unordered_set<string>>`
- O(1) friendship lookup, O(V+E) traversal
- Bidirectional edges for friend relationships

**Trie (C++)**
- Prefix search in O(k + results) time
- 26 child pointers per node (lowercase letters)
- Up to 10 results returned

**PageRank (C++)**
- 20 iterations, 0.85 damping factor
- Ranks users by influence in network
- Used for recommendation scoring

**FileManager (C++)**
- **Two-pass loading**: First pass builds maps, second resolves friend IDs
- Handles Windows CR characters (`\r`)
- Deterministic sorting by user ID
- Atomic save operations

**Express Server (Node.js)**
- Maps HTTP requests to CLI arguments
- Sets working directory for relative path resolution
- Timeout protection (10 seconds per command)
- Static file serving for HTML/CSS/JS

---

## 📊 Data Format

### CSV Structure (users.csv)
```
id,username,friend_ids
a1b2c3,alice,d4e5f6,g7h8i9
d4e5f6,bob,a1b2c3,j0k1l2
g7h8i9,charlie,a1b2c3
```

**Format**: `id,username,comma-separated-friend-ids`

- **id**: Unique hash (deterministic, based on username)
- **username**: Human-readable name
- **friends**: Comma-separated list of friend IDs

### How Two-Pass Loading Works

**Pass 1**: Build ID↔Username maps
- Read all entries, populate `idToUser` and `userToId`
- Create empty friend sets in adjacency list

**Pass 2**: Resolve friend relationships
- Use ID maps to convert friend IDs to usernames
- Works regardless of CSV row order

**Why**: Ensures friends appearing later in CSV are properly resolved

---

## ⚡ Performance

### Time Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Add User | O(1) | Hash insertion |
| Remove User | O(V) | Must update all edges |
| Add Friendship | O(1) | Set insertion |
| Get Friends | O(1) | Hash lookup |
| Search (Prefix) | O(k) | k = prefix length |
| Mutual Friends | O(min(deg(u1), deg(u2))) | Set intersection |
| PageRank | O(20 × (V + E)) | 20 iterations |
| Connection Check | O(V + E) | BFS traversal |
| Recommendations | O(V + E + V log V) | Score sort |

### Space Complexity
- **Graph**: O(V + E) for adjacency list
- **Trie**: O(26^k) worst case (k = avg prefix length)
- **Storage**: O(V + 2E) for friendships

---

## 🐛 Troubleshooting

### Server won't start
**Error**: `EADDRINUSE: address already in use`
- **Solution**: Port 5000 is taken. Either:
  - Kill process on port 5000: `netstat -ano | findstr :5000`
  - Change port in `server.js` line 7: `const PORT = 5001;`

### Backend executable not found
**Error**: `Cannot find social_graph_app.exe`
- **Solution**: Build the backend first:
  ```bash
  cd backend
  make clean
  make
  ```
 - **Note**: The Express server (`frontend/server.js`) references absolute paths for the backend executable and CSV file. Update `BACKEND_PATH`, `BACKEND_DIR`, and `CSV_PATH` to match your local layout. A relative example (if running server from `frontend/`) is:
   ```js
   const BACKEND_PATH = path.resolve('../backend/build/social_graph_app.exe');
   const BACKEND_DIR  = path.resolve('../backend');
   const CSV_PATH     = path.resolve('../backend/dataset/users.csv');
   ```

### CSV not loading
**Error**: `users.csv not found at...`
- **Solution**: Ensure `users.csv` exists in `backend/dataset/`
- Check absolute path in `frontend/server.js` line 11

### No recommendations showing
**Error**: Returns "No recommendations"
- **Solution**: 
  - User needs at least 1 mutual friend
  - Add more users and friendships first
  - Check if user exists with "Display All Users"

### Styling not loading
**Error**: Page looks plain without colors
- **Solution**: Clear browser cache (Ctrl+Shift+Delete)
- Ensure `style.css` is in `frontend/` folder

### Search not working
**Error**: No suggestions appearing
### Build errors due to static linking
**Error**: Linking or build fails with `-static` flags enabled
- **Explanation**: The `Makefile` includes `-static`, `-static-libgcc`, and `-static-libstdc++` flags which can cause failures on some toolchains.
- **Solution**: Edit `backend/Makefile` and remove `-static*` flags from `CXXFLAGS`, then rebuild. Example change:
  ```makefile
  # original
  CXXFLAGS := -std=c++23 -O2 -Wall -static -static-libgcc -static-libstdc++ -I src

  # changed for non-static build
  CXXFLAGS := -std=c++23 -O2 -Wall -I src
  ```
This produces a dynamically linked binary which often builds more reliably.

- **Solution**: Trie might not be rebuilt after user addition
- This is automatic, but try "Clear Graph" and restart

---

## 📝 Example Workflow

```bash
# 1. Build and start
cd backend && make && cd ../frontend && npm start

# 2. Add users (via web UI)
alice, bob, charlie, diana

# 3. Create friendships
alice ↔ bob
alice ↔ charlie
bob ↔ diana

# 4. Check recommendations
alice → recommendations shows: diana (mutual with bob)
charlie → recommendations shows: bob (mutual with alice)

# 5. Search functionality
type "ali" → autocomplete shows "alice"

# 6. PageRank
alice has highest score (connected to most users)
```

---

## 🎓 Learning Concepts

This project demonstrates:
- **Graph Theory**: Adjacency lists, BFS, connectivity
- **Algorithms**: PageRank, scoring functions
- **Data Structures**: Trie for prefix search, Hash maps for O(1) lookup
- **Systems Design**: CLI + API + Web layers
- **Persistence**: CSV format with two-pass loading
- **Full-Stack**: C++ backend + Node.js server + vanilla JS frontend

---

## 📄 License

MIT License - Feel free to modify and distribute

---

## 🤝 Contributing

Found a bug or want to improve?
1. Create a new branch: `git checkout -b feature/your-feature`
2. Make changes and test
3. Commit: `git commit -m "Add your feature"`
4. Push: `git push origin feature/your-feature`

---

## 📞 Support

For issues or questions:
1. Check the **Troubleshooting** section above
2. Review `backend/README.md` for C++ specifics
3. Check `frontend/server.js` for API configuration

---

**Created**: November 2025  
**Version**: 1.0.0  
**Status**: Production Ready ✅

From the `backend/` directory:

```bash
# Using Makefile (recommended)
make

# Or directly with g++
g++ -std=c++23 -O2 -I src src/**/*.cpp -o build/social_graph_app.exe
```

### Run

```bash
# Interactive menu mode (no arguments)
./build/social_graph_app.exe

# Silent mode (for API calls)
./build/social_graph_app.exe --silent
```

## CLI Commands

The program supports both **interactive menu** and **command-line arguments** for automation.

### Command-Line Arguments

```bash
# User Management
./app.exe --add <username>
./app.exe --remove <username>

# Friendship Operations
./app.exe --addFriend <user1> <user2>
./app.exe --removeFriend <user1> <user2>

# Friend Querying
./app.exe --friends <username>
./app.exe --mutual <user1> <user2>
./app.exe --connection <user1> <user2>

# Prefix Search (Trie)
./app.exe --search <prefix>

# PageRank & Recommendations
./app.exe --pagerank
./app.exe --recommend <username>

# Utility
./app.exe --clear
./app.exe --exit
```

### Interactive Menu

Run without arguments to get an interactive prompt:

```
===== Social Graph Menu =====
1. Add User
2. Remove User
3. Add Friendship
4. Remove Friendship
5. Display All Users
6. Get Friends of a User
7. Get Mutual Friends
8. Check Connection (via BFS)
9. Compute PageRank
10. Recommend Friends
11. Clear Graph
0. Exit
```

## CSV Format

Data is stored in `dataset/demousers.csv` (or `dataset/users.csv`):

```csv
c43459,gor,e773b2|a524ea|0b232c
a524ea,mena,0b232c|e773b2
0b232c,lalo,e773b2
e773b2,muthi,
```

**Format**: `id,username,friend_ids` where:
- `id` = 6-character hash (deterministic from username)
- `username` = readable name
- `friend_ids` = pipe-separated list of friend hash IDs (empty if no friends)

## Data Structures

### Graph (Adjacency List)
- Username → set of usernames (bidirectional friendships)
- Loaded from CSV on startup, persisted on save

### Trie (Prefix Search)
- Built from all current usernames
- Supports O(k) prefix searches (k = result count)
- Rebuilt when users are added/removed

### FileManager (Two-Pass CSV Loader)
- **Pass 1**: Parse all entries, build id↔username maps
- **Pass 2**: Resolve friend IDs to usernames
- Ensures friend references work regardless of CSV row order
- Auto-trims Windows CR (`\r`) for cross-platform compatibility

## Algorithms

### Friend Recommendation
**Score** = (# Mutual Friends) × (PageRank Influence)
- Recommends users with highest scores who aren't already friends
- Leverages both structural (mutual friends) and popularity (PageRank) metrics

### PageRank
- Damping factor: 0.85 (standard)
- Iterations: 20
- Represents user influence in the network

### Connection Detection (BFS)
- Finds if two users are connected by any path
- Useful for finding degrees of separation

## Frontend Integration

The frontend (`../frontend/server.js`) calls the backend via command-line arguments in **silent mode**:

```bash
./build/social_graph_app.exe --silent --search alice
./build/social_graph_app.exe --silent --add bob
```

All paths in `server.js` must point to:
- CSV: `backend/dataset/demousers.csv`
- EXE: `backend/build/social_graph_app.exe`
- Working Directory: `backend/`

## Performance Notes

- **Add/Remove User**: O(1) hash map insertion
- **Add/Remove Friendship**: O(1) set insertion
- **Get Friends**: O(n) to copy set to vector
- **Mutual Friends**: O(min(|friends1|, |friends2|))
- **BFS Connection**: O(V + E) in worst case
- **PageRank**: O(iterations × V × avg_degree)
- **Prefix Search**: O(prefix_length + result_count)

## Known Limitations

1. In-memory representation of graph; scales to millions of users/edges
2. CSV I/O is sequential; large datasets may have startup delay
3. No encryption on stored user data
4. No user authentication/authorization

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Build fails with "undefined reference" | Check all `.cpp` files are included in compile command |
| Friendships not loading | Verify CSV format is `id,username,friends` with correct delimiters |
| Prefix search returns nothing | Ensure Trie was rebuilt (happens on addUser/removeUser) |
| Frontend can't find executable | Update absolute paths in `frontend/server.js` |

## License

Academic project (DSA coursework)
