# Social Graph Friend Recommender (Backend)

A high-performance C++ social network engine combining **graph algorithms** for friend recommendations, **Trie-based autocomplete** for username search, and **PageRank** for influence scoring. Persistent CSV storage with hash-based user IDs.

## Features

- ✅ **User Management**: Add/remove users with deterministic hash IDs
- ✅ **Friendship Tracking**: Bidirectional friendship graph (adjacency list)
- ✅ **Friend Recommendation**: Score-based recommendations using mutual friends + PageRank influence
- ✅ **Connection Detection**: BFS-based path finding between users
- ✅ **Prefix Search**: Fast O(k) username autocomplete via Trie
- ✅ **PageRank Algorithm**: Compute influence scores for all users
- ✅ **Persistent Storage**: CSV-based data persistence with automatic load/save
- ✅ **CLI & API Modes**: Both interactive menu and command-line argument parsing
- ✅ **Silent Mode**: Suppress console output for API/frontend integration

## Project Structure

```
backend/
├── src/
│   ├── main.cpp              # Entry point, CLI & interactive menu
│   ├── graph/
│   │   ├── Graph.hpp         # Core graph class
│   │   └── Graph.cpp         # Graph implementation
│   ├── io/
│   │   ├── FileManager.hpp   # CSV persistence
│   │   └── FileManager.cpp   # Two-pass CSV loader & saver
│   ├── search/
│   │   ├── Trie.hpp          # Trie data structure
│   │   └── Trie.cpp          # Trie implementation
│   └── utils/
│       ├── utils.hpp         # Utility functions
│       └── Utils.cpp         # Hash ID generation
├── dataset/
│   ├── users.csv             # Main user data (id,username,friends)
│   ├── demousers.csv         # Demo dataset
│   └── searches.csv          # (Optional) search history
├── build/                     # Compiled object files & executable
├── Makefile                   # Build configuration
└── README.md                  # This file
```

## Building the Project

### Prerequisites
- **Windows**: MSYS2 with MinGW64 g++ (or any C++23-compatible compiler)
- **Linux/macOS**: g++ or clang with C++23 support

### Compile

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
