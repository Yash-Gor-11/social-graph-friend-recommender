const cliOutput = document.getElementById("cliOutput");
const suggestions = document.getElementById("suggestions");
const searchInput = document.getElementById("searchInput");

let usersCache = [];

function log(msg) {
  cliOutput.textContent += `\n> ${msg}`;
  cliOutput.scrollTop = cliOutput.scrollHeight;
}

async function loadUsers() {
  try {
    const res = await fetch("/users");
    const data = await res.json();
    usersCache = Array.isArray(data) ? data : [];
    log(`Loaded ${usersCache.length} users`);
  } catch (e) {
    log("❌ Failed to load users: " + e);
  }
}

function postAction(path, body) {
  return fetch(path, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(body)
  }).then((r) => r.json());
}

function setupButton(id, handler) {
  const el = document.getElementById(id);
  if (el) el.onclick = handler;
}

// === ACTIONS ===
setupButton("addBtn", async () => {
  const name = document.getElementById("username").value.trim();
  if (!name) return alert("Enter username");
  const res = await postAction("/add", { username: name });
  log(`➕ ${res.output}`);
  loadUsers();
});

setupButton("removeBtn", async () => {
  const name = document.getElementById("username").value.trim();
  if (!name) return alert("Enter username");
  const res = await postAction("/remove", { username: name });
  log(`🗑️ ${res.output}`);
  loadUsers();
});

setupButton("addFriendBtn", async () => {
  const a = document.getElementById("userA").value.trim();
  const b = document.getElementById("userB").value.trim();
  if (!a || !b) return alert("Enter both usernames");
  const res = await postAction("/addFriend", { a, b });
  log(`🔗 ${res.output}`);
});

setupButton("removeFriendBtn", async () => {
  const a = document.getElementById("userA").value.trim();
  const b = document.getElementById("userB").value.trim();
  if (!a || !b) return alert("Enter both usernames");
  const res = await postAction("/removeFriend", { a, b });
  log(`❌ ${res.output}`);
});

setupButton("displayAllBtn", async () => {
  const res = await fetch("/users");
  const data = await res.json();
  log("👥 All Users:\n" + data.join(", "));
});

setupButton("clearGraphBtn", async () => {
  if (!confirm("Are you sure? This will clear the graph.")) return;
  const res = await postAction("/clear", {});
  log(`⚠️ ${res.output}`);
});

setupButton("getFriendsBtn", async () => {
  const u = document.getElementById("singleUser").value.trim();
  if (!u) return alert("Enter username");
  const res = await fetch(`/friends?q=${encodeURIComponent(u)}`).then((r) =>
    r.json()
  );
  log(`🤝 ${res.output}`);
});

setupButton("mutualBtn", async () => {
  const u1 = document.getElementById("mutualUser1").value.trim();
  const u2 = document.getElementById("mutualUser2").value.trim();
  if (!u1 || !u2) return alert("Enter both usernames");
  const res = await fetch(`/mutual?a=${encodeURIComponent(u1)}&b=${encodeURIComponent(u2)}`).then((r) =>
    r.json()
  );
  log(`🤝 ${res.output}`);
});

setupButton("pagerankBtn", async () => {
  const u = document.getElementById("singleUser").value.trim();
  if (!u) return alert("Enter username");
  const res = await fetch(`/pagerank?q=${encodeURIComponent(u)}`).then((r) =>
    r.json()
  );
  log(`📈 ${res.output}`);
});

setupButton("checkConnBtn", async () => {
  const a = document.getElementById("connA").value.trim();
  const b = document.getElementById("connB").value.trim();
  if (!a || !b) return alert("Enter both usernames");
  const res = await fetch(
    `/connection?a=${encodeURIComponent(a)}&b=${encodeURIComponent(b)}`
  ).then((r) => r.json());
  log(`🔍 ${res.output}`);
});

setupButton("recommendBtn", async () => {
  const u = document.getElementById("recommendInput").value.trim();
  if (!u) return alert("Enter username for recommendations");
  const res = await fetch(`/recommend?q=${encodeURIComponent(u)}`).then((r) =>
    r.json()
  );
  log(`💡 ${res.output}`);
});

// === Search Suggestions ===
searchInput.addEventListener("input", async () => {
  const q = searchInput.value.trim();
  suggestions.innerHTML = '';
  if (!q) return suggestions.classList.add('hidden');

  const res = await fetch(`/search?q=${encodeURIComponent(q)}`);
  const data = await res.json();

  if (!data.length) return suggestions.classList.add('hidden');
  data.slice(0, 12).forEach(u => {
    const li = document.createElement('li');
    li.textContent = u;
    li.onclick = () => {
      searchInput.value = u;
      suggestions.classList.add('hidden');
      log(`Selected: ${u}`);
    };
    suggestions.appendChild(li);
  });
  suggestions.classList.remove('hidden');
});

document.addEventListener("click", (e) => {
  if (!searchInput.contains(e.target) && !suggestions.contains(e.target))
    suggestions.classList.add("hidden");
});

window.onload = loadUsers;
