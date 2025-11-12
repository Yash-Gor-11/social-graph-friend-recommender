const canvas = document.getElementById("background");
const ctx = canvas.getContext("2d");

let particles = [];
const particleCount = 80;
const maxSpeed = 0.25;
const connectDistance = 160;

// Handle resize
function resizeCanvas() {
  canvas.width = innerWidth;
  canvas.height = innerHeight;
}
resizeCanvas();
window.addEventListener("resize", resizeCanvas);

// Initialize particles with enhanced properties
function initParticles() {
  particles = [];
  for (let i = 0; i < particleCount; i++) {
    particles.push({
      x: Math.random() * canvas.width,
      y: Math.random() * canvas.height,
      vx: (Math.random() - 0.5) * maxSpeed,
      vy: (Math.random() - 0.5) * maxSpeed,
      r: Math.random() * 2.5 + 1.2,
      opacity: Math.random() * 0.5 + 0.5,
      pulsePhase: Math.random() * Math.PI * 2,
      pulseSpeed: Math.random() * 0.02 + 0.005,
    });
  }
}
initParticles();

// Animation loop with enhanced visuals
function animate() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Animated gradient background
  const time = Date.now() * 0.0001;
  const gradient = ctx.createLinearGradient(
    Math.sin(time) * 100,
    Math.cos(time) * 100,
    canvas.width + Math.sin(time + 1) * 100,
    canvas.height + Math.cos(time + 1) * 100
  );
  gradient.addColorStop(0, "#050505");
  gradient.addColorStop(0.5, "#0a0f1a");
  gradient.addColorStop(1, "#0b0f16");
  ctx.fillStyle = gradient;
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  // Draw connections with better visuals
  for (let i = 0; i < particles.length; i++) {
    for (let j = i + 1; j < particles.length; j++) {
      const dx = particles[i].x - particles[j].x;
      const dy = particles[i].y - particles[j].y;
      const dist = Math.sqrt(dx * dx + dy * dy);
      if (dist < connectDistance) {
        const opacity = (1 - dist / connectDistance) * 0.3;
        const hue = (Math.atan2(dy, dx) * 180 / Math.PI + 180) % 360;
        ctx.strokeStyle = `hsla(${hue}, 100%, 50%, ${opacity})`;
        ctx.lineWidth = 0.8;
        ctx.beginPath();
        ctx.moveTo(particles[i].x, particles[i].y);
        ctx.lineTo(particles[j].x, particles[j].y);
        ctx.stroke();
      }
    }
  }

  // Draw particles with pulsing effect
  for (let p of particles) {
    // Pulsing radius effect
    p.pulsePhase += p.pulseSpeed;
    const pulseRadius = p.r * (1 + Math.sin(p.pulsePhase) * 0.4);

    // Glow effect
    const gradient = ctx.createRadialGradient(p.x, p.y, 0, p.x, p.y, pulseRadius * 3);
    gradient.addColorStop(0, `rgba(0, 198, 255, ${p.opacity * 0.6})`);
    gradient.addColorStop(1, `rgba(0, 198, 255, 0)`);
    ctx.fillStyle = gradient;
    ctx.fillRect(p.x - pulseRadius * 3, p.y - pulseRadius * 3, pulseRadius * 6, pulseRadius * 6);

    // Core particle
    ctx.beginPath();
    ctx.arc(p.x, p.y, pulseRadius, 0, Math.PI * 2);
    ctx.fillStyle = `rgba(0, 200, 255, ${p.opacity})`;
    ctx.fill();

    // Bright center
    ctx.beginPath();
    ctx.arc(p.x, p.y, pulseRadius * 0.5, 0, Math.PI * 2);
    ctx.fillStyle = `rgba(255, 255, 255, ${p.opacity * 0.8})`;
    ctx.fill();

    // Update position
    p.x += p.vx;
    p.y += p.vy;

    // Bounce at edges with smoothing
    if (p.x < 0 || p.x > canvas.width) p.vx *= -1;
    if (p.y < 0 || p.y > canvas.height) p.vy *= -1;

    // Keep particles in bounds
    if (p.x < 0) p.x = 0;
    if (p.x > canvas.width) p.x = canvas.width;
    if (p.y < 0) p.y = 0;
    if (p.y > canvas.height) p.y = canvas.height;
  }

  requestAnimationFrame(animate);
}

animate();
