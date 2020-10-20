/*
  Johan Karlsson, 2019
  https://twitter.com/DonKarlssonSan
  MIT License, see Details View
*/
let canvas;
let ctx;
let w, h;
let imageBuffer;
let offset;

function setup() {
  offset = 0;
  canvas = document.querySelector("#canvas");
  ctx = canvas.getContext("2d");
  reset();
  window.addEventListener("resize", reset);
}

function reset() {
  w = canvas.width = window.innerWidth;
  h = canvas.height = window.innerHeight;
  ctx.strokeStyle = "white";
  ctx.lineWidth = 2;
  storeHeartInBuffer();
}

function draw() {
  requestAnimationFrame(draw);
  ctx.fillRect(0, 0, w, h);
  offset += 0.5;
  drawHeartLines();
}

function storeHeartInBuffer() {
  ctx.beginPath();
  for (let angle = 0; angle < Math.PI * 2; angle += 0.01) {
    let r = Math.min(w, h) * 0.025;
    let x = r * 16 * Math.pow(Math.sin(angle), 3);
    let y = -r * (13 * Math.cos(angle) - 5 * Math.cos(2 * angle) - 2 * Math.cos(3 * angle) - Math.cos(4 * angle));
    ctx.lineTo(w / 2 + x, h * 0.45 + y);
  }
  ctx.fill();

  let image = ctx.getImageData(0, 0, w, h);
  imageBuffer = new Uint32Array(image.data.buffer);
}

function drawHeartLines() {
  let step = 20;
  for (let y = 0; y < h; y += step) {
    drawHeartLine(y + offset % step);
  }
}

function drawHeartLine(y) {
  ctx.beginPath();
  let y1;
  for (let x = 0; x < w; x += 2) {
    if (imageBuffer[Math.floor(y) * w + x]) {
      let n = 10;
      y1 = y + n;
    } else {
      y1 = y;
    }
    ctx.lineTo(x, y1);
  }
  ctx.stroke();
}

setup();
draw();