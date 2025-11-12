const canvas = document.getElementById("background");
const ctx = canvas.getContext("2d");

let particles = [];
const particleCount = 60;
const maxSpeed = 0.3;
const connectDistance = 150;

// Handle resize
function resizeCanvas() {
  canvas.width = innerWidth;
  canvas.height = innerHeight;
}
resizeCanvas();
window.addEventListener("resize", resizeCanvas);

// Initialize particles
function initParticles() {
  particles = [];
  for (let i = 0; i < particleCount; i++) {
    particles.push({
      x: Math.random() * canvas.width,
      y: Math.random() * canvas.height,
      vx: (Math.random() - 0.5) * maxSpeed,
      vy: (Math.random() - 0.5) * maxSpeed,
      r: Math.random() * 2 + 1,
    });
  }
}
initParticles();

// Animation loop
function animate() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // soft background gradient
  const gradient = ctx.createLinearGradient(0, 0, canvas.width, canvas.height);
  gradient.addColorStop(0, "#050505");
  gradient.addColorStop(1, "#0b0f16");
  ctx.fillStyle = gradient;
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  // draw connections
  for (let i = 0; i < particles.length; i++) {
    for (let j = i + 1; j < particles.length; j++) {
      const dx = particles[i].x - particles[j].x;
      const dy = particles[i].y - particles[j].y;
      const dist = Math.sqrt(dx * dx + dy * dy);
      if (dist < connectDistance) {
        const opacity = 1 - dist / connectDistance;
        ctx.strokeStyle = `rgba(0, 150, 255, ${opacity * 0.2})`;
        ctx.lineWidth = 0.5;
        ctx.beginPath();
        ctx.moveTo(particles[i].x, particles[i].y);
        ctx.lineTo(particles[j].x, particles[j].y);
        ctx.stroke();
      }
    }
  }

  // draw particles
  for (let p of particles) {
    ctx.beginPath();
    ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(0,150,255,0.8)";
    ctx.fill();

    p.x += p.vx;
    p.y += p.vy;

    // bounce at edges
    if (p.x < 0 || p.x > canvas.width) p.vx *= -1;
    if (p.y < 0 || p.y > canvas.height) p.vy *= -1;
  }

  requestAnimationFrame(animate);
}

animate();
