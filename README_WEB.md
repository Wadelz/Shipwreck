# Wave Break - Web Version

A web-based port of the Shipwreck rescue game. Navigate dangerous waves in your rowboat to rescue 6 survivors and reach the flag!

## 🎮 How to Play

- **Arrow Keys**: Move your rowboat
- **Space**: Start game / Restart after game over
- **Objective**: Rescue all 6 survivors from the ocean and reach the flag
- **Strategy**: Hide behind rocks to avoid waves (they create safe zones)
- **Challenge**: Your boat slows down after rescuing 4 survivors!

## 🚀 Running Locally

### Option 1: Simple HTTP Server (Recommended)

```bash
# Using Python 3
cd /home/user/Shipwreck
python3 -m http.server 8000

# Using Python 2
python -m SimpleHTTPServer 8000

# Using Node.js (npx)
npx http-server -p 8000

# Using PHP
php -S localhost:8000
```

Then open your browser to: `http://localhost:8000`

### Option 2: Direct File Access

Simply open `index.html` in your web browser. Note: Some browsers may restrict loading external assets when opening files directly. Use the HTTP server method if you encounter issues.

## 📦 Deploying to Your Portfolio

### Option 1: GitHub Pages

1. Push these files to a GitHub repository:
   ```bash
   git add index.html game.js README_WEB.md
   git commit -m "Add web version of Wave Break game"
   git push origin main
   ```

2. Enable GitHub Pages:
   - Go to repository Settings
   - Navigate to "Pages" section
   - Select branch (main) and folder (root or /docs)
   - Save and wait for deployment

3. Your game will be live at: `https://username.github.io/repository-name/`

### Option 2: Netlify (Drag & Drop)

1. Go to [netlify.com](https://www.netlify.com/)
2. Sign up for a free account
3. Drag and drop the Shipwreck folder onto the Netlify dashboard
4. Get instant deployment with a custom URL

### Option 3: Vercel

```bash
# Install Vercel CLI
npm i -g vercel

# Deploy from the Shipwreck directory
cd /home/user/Shipwreck
vercel
```

### Option 4: Your Own Website

Simply upload these files to your web hosting:
- `index.html`
- `game.js`
- (Optional) The `Shipwreck/assets/` folder for original graphics

The game uses a CDN for Phaser 3, so no additional dependencies needed!

## 🎨 Using Original Assets

The game will automatically try to load the original C++ version's assets from `Shipwreck/assets/`. If they're not found, it will use programmatically generated graphics.

To use the original graphics, ensure this folder structure:
```
/
├── index.html
├── game.js
└── Shipwreck/
    └── assets/
        ├── RowBoatC.png
        ├── WavesHalf.png
        ├── Rock2_1.png
        ├── Flag2k.png
        ├── head.png
        └── easterBeachBall.png
```

## 🔧 Customization

### Change Game Difficulty

Edit `game.js` to adjust:
- `lives: 3` - Starting lives
- `wave.setData('speed', 2)` - Wave speed
- `ship.setData('speed', 5)` - Ship speed
- Wave count and positions

### Styling

Edit the `<style>` section in `index.html` to customize:
- Background gradient
- Game container shadow/border
- Responsive layout

### Resolution

Change the game size in `game.js`:
```javascript
const config = {
    width: 1024,  // Change width
    height: 768,  // Change height
    // ...
};
```

## 🌐 Browser Compatibility

Works on all modern browsers:
- ✅ Chrome/Edge (recommended)
- ✅ Firefox
- ✅ Safari
- ✅ Opera
- ✅ Mobile browsers

## 📝 Technical Details

- **Framework**: Phaser 3.70.0 (via CDN)
- **Original Version**: C++ with SFML
- **Resolution**: 1024x768 pixels
- **No build process required**
- **No external dependencies** (Phaser loaded from CDN)

## 🎯 Game Features Ported

- ✅ Ship movement with arrow keys
- ✅ Wave obstacles that move down the screen
- ✅ 6 survivors to collect
- ✅ 4 rock safe zones
- ✅ Flag appears after collecting all survivors
- ✅ Speed reduction after 4 survivors
- ✅ Lives system (3 lives)
- ✅ Score tracking
- ✅ Timer
- ✅ Win/loss conditions
- ✅ Instructions screen

## 🐛 Troubleshooting

**Images not loading?**
- Ensure you're running via HTTP server (not file://)
- Check that assets folder path is correct
- The game will work with programmatic graphics as fallback

**Game not starting?**
- Check browser console for errors (F12)
- Ensure JavaScript is enabled
- Try a different browser

**Performance issues?**
- Close other browser tabs
- Try disabling browser extensions
- The game is optimized for 60 FPS

## 📜 License

Based on the original Shipwreck C++ game. Web port created for portfolio use.

---

Enjoy rescuing survivors! 🚣‍♂️🌊
