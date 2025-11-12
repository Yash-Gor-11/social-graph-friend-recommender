// // UI wiring for all features
// const cliOutput = document.getElementById("cliOutput");
// const suggestions = document.getElementById("suggestions");
// const searchInput = document.getElementById("searchInput");

// const usernameInput = document.getElementById("username");
// const addBtn = document.getElementById("addBtn");
// const removeBtn = document.getElementById("removeBtn");

// const userA = document.getElementById("userA");
// const userB = document.getElementById("userB");
// const addFriendBtn = document.getElementById("addFriendBtn");
// const removeFriendBtn = document.getElementById("removeFriendBtn");

// const displayAllBtn = document.getElementById("displayAllBtn");
// const clearGraphBtn = document.getElementById("clearGraphBtn");

// const singleUser = document.getElementById("singleUser");
// const getFriendsBtn = document.getElementById("getFriendsBtn");
// const mutualBtn = document.getElementById("mutualBtn");
// const pagerankBtn = document.getElementById("pagerankBtn");

// const connA = document.getElementById("connA");
// const connB = document.getElementById("connB");
// const checkConnBtn = document.getElementById("checkConnBtn");
// const recommendBtn = document.getElementById("recommendBtn");

// let usersCache = [];

// function log(msg){
//   cliOutput.textContent = `> ${msg}\n${cliOutput.textContent}`;
// }

// // load users (reads CSV via /users)
// function loadUsers(){
//   fetch('/users').then(r=>r.json()).then(data=>{
//     usersCache = Array.isArray(data) ? data : [];
//     log(`Loaded ${usersCache.length} users`);
//   }).catch(e => log('Failed to load users: ' + e));
// }

// // helper POST wrapper
// function postAction(path, body){
//   return fetch(path, {
//     method:'POST',
//     headers:{ 'Content-Type':'application/json' },
//     body: JSON.stringify(body)
//   }).then(r => r.json());
// }

// /* basic user operations */
// addBtn.onclick = ()=> {
//   const name = usernameInput.value.trim();
//   if(!name) return alert('enter username');
//   postAction('/add', { username: name })
//     .then(res => { log(`ADD → ${res.output}`); loadUsers(); usernameInput.value=''; });
// };

// removeBtn.onclick = ()=> {
//   const name = usernameInput.value.trim();
//   if(!name) return alert('enter username');
//   postAction('/remove', { username: name })
//     .then(res => { log(`REMOVE → ${res.output}`); loadUsers(); usernameInput.value=''; });
// };

// /* friendship */
// addFriendBtn.onclick = ()=> {
//   const a = userA.value.trim(), b = userB.value.trim();
//   if(!a||!b) return alert('enter both users');
//   postAction('/addFriend', { a, b }).then(res => { log(`ADD FRIEND → ${res.output}`); loadUsers(); userA.value=''; userB.value=''; });
// };

// removeFriendBtn.onclick = ()=> {
//   const a = userA.value.trim(), b = userB.value.trim();
//   if(!a||!b) return alert('enter both users');
//   postAction('/removeFriend', { a, b }).then(res => { log(`REMOVE FRIEND → ${res.output}`); loadUsers(); userA.value=''; userB.value=''; });
// };

// /* display, clear */
// displayAllBtn.onclick = ()=> {
//   fetch('/users').then(r=>r.json()).then(data=>{
//     log('ALL USERS:\n' + (Array.isArray(data)?data.join(', '):String(data)));
//   });
// };

// clearGraphBtn.onclick = ()=> {
//   if(!confirm('Clear entire graph? This will delete all nodes.')) return;
//   postAction('/clear', {}).then(res => { log(`CLEAR → ${res.output}`); loadUsers(); });
// };

// /* friends / mutual / pagerank */
// getFriendsBtn.onclick = ()=> {
//   const u = singleUser.value.trim();
//   if(!u) return alert('enter username');
//   fetch(`/friends?q=${encodeURIComponent(u)}`).then(r=>r.json()).then(res=>{
//     log(`FRIENDS(${u}): ${res.output}`);
//   });
// };

// mutualBtn.onclick = ()=> {
//   const u = singleUser.value.trim();
//   if(!u) return alert('enter username');
//   fetch(`/mutual?q=${encodeURIComponent(u)}`).then(r=>r.json()).then(res=>{
//     log(`MUTUAL(${u}): ${res.output}`);
//   });
// };

// pagerankBtn.onclick = ()=> {
//   const u = singleUser.value.trim();
//   if(!u) return alert('enter username');
//   fetch(`/pagerank?q=${encodeURIComponent(u)}`).then(r=>r.json()).then(res=>{
//     log(`PAGERANK(${u}): ${res.output}`);
//   });
// };

// /* connection and recommend */
// checkConnBtn.onclick = ()=> {
//   const a = connA.value.trim(), b = connB.value.trim();
//   if(!a||!b) return alert('enter both users');
//   fetch(`/connection?a=${encodeURIComponent(a)}&b=${encodeURIComponent(b)}`).then(r=>r.json()).then(res=>{
//     log(`CONNECTION(${a}↔${b}): ${res.output}`);
//   });
// };

// recommendBtn.onclick = ()=> {
//   const u = connA.value.trim();
//   if(!u) return alert('enter a username into Connection A (for recommendations)');
//   fetch(`/recommend?q=${encodeURIComponent(u)}`).then(r=>r.json()).then(res=>{
//     log(`RECOMMEND(${u}): ${res.output}`);
//   });
// };

// /* search suggestions (frontend-based until backend trie is ready) */
// searchInput.addEventListener('input', ()=>{
//   const q = searchInput.value.trim().toLowerCase();
//   suggestions.innerHTML = '';
//   if(!q){ suggestions.classList.add('hidden'); return; }
//   const filtered = usersCache.filter(u => u.toLowerCase().includes(q)).slice(0, 12);
//   if(!filtered.length){ suggestions.classList.add('hidden'); return; }
//   filtered.forEach(u => {
//     const li = document.createElement('li'); li.textContent = u;
//     li.onclick = ()=>{ searchInput.value = u; suggestions.classList.add('hidden'); log('Selected: ' + u); };
//     suggestions.appendChild(li);
//   });
//   suggestions.classList.remove('hidden');
// });

// /* hide suggestions when clicking outside */
// document.addEventListener('click', (e)=> {
//   if(!searchInput.contains(e.target) && !suggestions.contains(e.target)) suggestions.classList.add('hidden');
// });

// window.onload = loadUsers;
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
  const u = document.getElementById("singleUser").value.trim();
  if (!u) return alert("Enter username");
  const res = await fetch(`/mutual?q=${encodeURIComponent(u)}`).then((r) =>
    r.json()
  );
  log(`🫱🏻‍🫲🏽 ${res.output}`);
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
  const u = document.getElementById("connA").value.trim();
  if (!u) return alert("Enter username in Connection A");
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
