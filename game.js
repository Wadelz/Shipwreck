// Wave Break - Shipwreck Rescue Game
// Web port of the C++ SFML version

class GameScene extends Phaser.Scene {
    constructor() {
        super({ key: 'GameScene' });
        this.score = 0;
        this.lives = 3;
        this.gameTime = 0;
        this.gameStarted = false;
        this.gameWon = false;
        this.gameLost = false;
        this.survivorsCollected = 0;
        this.totalSurvivors = 6;
        this.frameCount = 0;
    }

    preload() {
        // Check if assets exist, otherwise we'll create programmatic graphics
        this.load.on('fileerror', (file) => {
            console.log('Asset not found, will use programmatic graphics:', file.key);
        });

        // Try to load assets from the Shipwreck/assets folder
        this.load.image('ship', 'Shipwreck/assets/RowBoatC.png');
        this.load.image('wave', 'Shipwreck/assets/WavesHalf.png');
        this.load.image('rock', 'Shipwreck/assets/Rock2_1.png');
        this.load.image('flag', 'Shipwreck/assets/Flag2k.png');
        this.load.image('survivor', 'Shipwreck/assets/head.png');
        this.load.image('ball', 'Shipwreck/assets/easterBeachBall.png');
    }

    create() {
        // Set background color (ocean blue)
        this.cameras.main.setBackgroundColor('#1A80B6');

        // Create graphics object for programmatic shapes
        this.graphics = this.add.graphics();

        // Initialize game objects
        this.createRocks();
        this.createShip();
        this.createWaves();
        this.createSurvivors();
        this.createFlag();
        this.createUI();
        this.setupInput();

        // Start game timer
        this.time.addEvent({
            delay: 1000,
            callback: this.updateTimer,
            callbackScope: this,
            loop: true
        });

        // Show instructions
        this.showInstructions();
    }

    createShip() {
        // Ship starting position
        const startX = 512;
        const startY = 650;
        const shipWidth = 60;
        const shipHeight = 40;

        if (this.textures.exists('ship')) {
            this.ship = this.add.sprite(startX, startY, 'ship');
            this.ship.setScale(0.5);
        } else {
            // Create programmatic ship (rowboat shape)
            const shipGraphics = this.add.graphics();
            shipGraphics.fillStyle(0x8B4513, 1); // Brown color
            shipGraphics.fillRect(0, 0, shipWidth, shipHeight);
            shipGraphics.fillStyle(0xD2691E, 1); // Lighter brown for detail
            shipGraphics.fillRect(5, 5, shipWidth - 10, shipHeight - 10);
            shipGraphics.generateTexture('ship_generated', shipWidth, shipHeight);
            shipGraphics.destroy();

            this.ship = this.add.sprite(startX, startY, 'ship_generated');
        }

        this.ship.setData('speed', 5);
        this.ship.setData('normalSpeed', 5);
        this.ship.setData('slowSpeed', 3);
    }

    createWaves() {
        this.waves = [];
        const waveWidth = 1024;
        const waveHeight = 80;

        // Create 3 waves at different positions
        const wavePositions = [
            { x: 512, y: 100 },
            { x: 512, y: 300 },
            { x: 512, y: 500 }
        ];

        wavePositions.forEach((pos, index) => {
            let wave;
            if (this.textures.exists('wave')) {
                wave = this.add.sprite(pos.x, pos.y, 'wave');
                wave.setDisplaySize(waveWidth, waveHeight);
            } else {
                // Create programmatic wave
                const waveGraphics = this.add.graphics();
                waveGraphics.fillStyle(0x4169E1, 0.7); // Royal blue, semi-transparent
                waveGraphics.fillRect(0, 0, waveWidth, waveHeight);
                waveGraphics.fillStyle(0xFFFFFF, 0.3); // White foam
                waveGraphics.fillRect(0, 0, waveWidth, 20);
                waveGraphics.generateTexture('wave_generated_' + index, waveWidth, waveHeight);
                waveGraphics.destroy();

                wave = this.add.sprite(pos.x, pos.y, 'wave_generated_' + index);
            }

            wave.setData('speed', 2);
            wave.setData('initialY', pos.y);
            this.waves.push(wave);
        });
    }

    createRocks() {
        this.rocks = [];
        const rockSize = 100;

        // 4 rocks positioned around the map as safe zones
        const rockPositions = [
            { x: 200, y: 200 },
            { x: 824, y: 200 },
            { x: 200, y: 500 },
            { x: 824, y: 500 }
        ];

        rockPositions.forEach((pos, index) => {
            let rock;
            if (this.textures.exists('rock')) {
                rock = this.add.sprite(pos.x, pos.y, 'rock');
                rock.setDisplaySize(rockSize, rockSize);
            } else {
                // Create programmatic rock
                const rockGraphics = this.add.graphics();
                rockGraphics.fillStyle(0x808080, 1); // Gray
                rockGraphics.fillCircle(rockSize / 2, rockSize / 2, rockSize / 2);
                rockGraphics.fillStyle(0x696969, 1); // Darker gray for detail
                rockGraphics.fillCircle(rockSize / 2 - 10, rockSize / 2 - 10, rockSize / 3);
                rockGraphics.generateTexture('rock_generated_' + index, rockSize, rockSize);
                rockGraphics.destroy();

                rock = this.add.sprite(pos.x, pos.y, 'rock_generated_' + index);
            }

            // Create safe zone overlay (semi-transparent circle)
            const safeZone = this.add.circle(pos.x, pos.y, rockSize * 1.2, 0x00FF00, 0.1);
            rock.setData('safeZone', safeZone);
            rock.setData('safeRadius', rockSize * 1.2);

            this.rocks.push(rock);
        });
    }

    createSurvivors() {
        this.survivors = [];
        const survivorSize = 30;

        // 6 survivors scattered around the map
        const survivorPositions = [
            { x: 150, y: 150 },
            { x: 874, y: 150 },
            { x: 512, y: 250 },
            { x: 150, y: 450 },
            { x: 874, y: 450 },
            { x: 512, y: 550 }
        ];

        survivorPositions.forEach((pos, index) => {
            let survivor;
            if (this.textures.exists('survivor')) {
                survivor = this.add.sprite(pos.x, pos.y, 'survivor');
                survivor.setDisplaySize(survivorSize, survivorSize);
            } else {
                // Create programmatic survivor (person in water)
                const survivorGraphics = this.add.graphics();
                survivorGraphics.fillStyle(0xFFDBAC, 1); // Skin tone
                survivorGraphics.fillCircle(survivorSize / 2, survivorSize / 2, survivorSize / 2);
                survivorGraphics.fillStyle(0xFF6347, 1); // Red life vest
                survivorGraphics.fillRect(survivorSize / 4, survivorSize / 2, survivorSize / 2, survivorSize / 3);
                survivorGraphics.generateTexture('survivor_generated_' + index, survivorSize, survivorSize);
                survivorGraphics.destroy();

                survivor = this.add.sprite(pos.x, pos.y, 'survivor_generated_' + index);
            }

            survivor.setData('collected', false);
            this.survivors.push(survivor);
        });
    }

    createFlag() {
        const flagX = 512;
        const flagY = 50;
        const flagWidth = 60;
        const flagHeight = 80;

        if (this.textures.exists('flag')) {
            this.flag = this.add.sprite(flagX, flagY, 'flag');
            this.flag.setDisplaySize(flagWidth, flagHeight);
        } else {
            // Create programmatic flag
            const flagGraphics = this.add.graphics();
            flagGraphics.fillStyle(0x8B4513, 1); // Brown pole
            flagGraphics.fillRect(flagWidth / 2 - 3, 0, 6, flagHeight);
            flagGraphics.fillStyle(0xFF0000, 1); // Red flag
            flagGraphics.fillRect(flagWidth / 2, 5, flagWidth / 2 - 5, flagHeight / 2);
            flagGraphics.generateTexture('flag_generated', flagWidth, flagHeight);
            flagGraphics.destroy();

            this.flag = this.add.sprite(flagX, flagY, 'flag_generated');
        }

        this.flag.setVisible(false);
        this.flag.setData('appeared', false);
    }

    createUI() {
        const style = { font: '24px Arial', fill: '#ffffff' };

        this.scoreText = this.add.text(20, 20, 'Score: 0', style);
        this.livesText = this.add.text(20, 50, 'Lives: 3', style);
        this.timerText = this.add.text(20, 80, 'Time: 0s', style);
        this.survivorsText = this.add.text(20, 110, 'Survivors: 0/6', style);

        // Instructions text (will be hidden after game starts)
        this.instructionsText = this.add.text(512, 384, '', {
            font: '20px Arial',
            fill: '#ffffff',
            backgroundColor: '#000000',
            padding: { x: 20, y: 20 },
            align: 'center'
        });
        this.instructionsText.setOrigin(0.5);
    }

    showInstructions() {
        this.instructionsText.setText(
            'WAVE BREAK - Rescue Mission\n\n' +
            'Use ARROW KEYS to move your rowboat\n' +
            'Rescue all 6 survivors from the ocean\n' +
            'Hide behind ROCKS to avoid waves\n' +
            'Reach the FLAG after collecting all survivors\n\n' +
            'Press SPACE to start!'
        );
    }

    setupInput() {
        this.cursors = this.input.keyboard.createCursorKeys();
        this.spaceKey = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

        // Start game on space key
        this.spaceKey.on('down', () => {
            if (!this.gameStarted && !this.gameWon && !this.gameLost) {
                this.startGame();
            } else if (this.gameWon || this.gameLost) {
                this.restartGame();
            }
        });
    }

    startGame() {
        this.gameStarted = true;
        this.instructionsText.setVisible(false);
    }

    update(time, delta) {
        if (!this.gameStarted || this.gameWon || this.gameLost) {
            return;
        }

        this.frameCount++;

        // Update ship movement
        this.updateShipMovement();

        // Update waves
        this.updateWaves();

        // Check collisions
        this.checkCollisions();

        // Animate waves and flag (every 100 frames like original)
        if (this.frameCount % 100 === 0) {
            this.animateObjects();
        }
    }

    updateShipMovement() {
        const speed = this.ship.getData('speed');

        if (this.cursors.left.isDown) {
            this.ship.x -= speed;
        }
        if (this.cursors.right.isDown) {
            this.ship.x += speed;
        }
        if (this.cursors.up.isDown) {
            this.ship.y -= speed;
        }
        if (this.cursors.down.isDown) {
            this.ship.y += speed;
        }

        // Keep ship in bounds
        this.ship.x = Phaser.Math.Clamp(this.ship.x, 30, 1024 - 30);
        this.ship.y = Phaser.Math.Clamp(this.ship.y, 30, 768 - 30);
    }

    updateWaves() {
        this.waves.forEach(wave => {
            wave.y += wave.getData('speed');

            // Reset wave to top when it goes off bottom
            if (wave.y > 800) {
                wave.y = -40;
            }
        });
    }

    animateObjects() {
        // Simple animation: slightly move waves side to side
        this.waves.forEach((wave, index) => {
            wave.x += (index % 2 === 0) ? 10 : -10;
            if (wave.x < 400) wave.x = 400;
            if (wave.x > 624) wave.x = 624;
        });
    }

    checkCollisions() {
        // Check survivor collection
        this.survivors.forEach(survivor => {
            if (!survivor.getData('collected') &&
                Phaser.Math.Distance.Between(this.ship.x, this.ship.y, survivor.x, survivor.y) < 40) {
                this.collectSurvivor(survivor);
            }
        });

        // Check wave collisions
        let hitByWave = false;
        this.waves.forEach(wave => {
            if (Phaser.Geom.Intersects.RectangleToRectangle(
                this.ship.getBounds(),
                wave.getBounds()
            )) {
                hitByWave = true;
            }
        });

        // Check if in safe zone (near a rock)
        let inSafeZone = false;
        this.rocks.forEach(rock => {
            const distance = Phaser.Math.Distance.Between(this.ship.x, this.ship.y, rock.x, rock.y);
            if (distance < rock.getData('safeRadius')) {
                inSafeZone = true;
            }
        });

        // Lose life if hit by wave and not in safe zone
        if (hitByWave && !inSafeZone) {
            this.loseLife();
        }

        // Check flag collision (only if all survivors collected)
        if (this.survivorsCollected === this.totalSurvivors &&
            this.flag.getData('appeared') &&
            Phaser.Math.Distance.Between(this.ship.x, this.ship.y, this.flag.x, this.flag.y) < 60) {
            this.winGame();
        }
    }

    collectSurvivor(survivor) {
        survivor.setData('collected', true);
        survivor.setVisible(false);
        this.survivorsCollected++;
        this.score++;

        this.scoreText.setText('Score: ' + this.score);
        this.survivorsText.setText('Survivors: ' + this.survivorsCollected + '/' + this.totalSurvivors);

        // Reduce speed after 4 survivors (like original)
        if (this.survivorsCollected === 4) {
            this.ship.setData('speed', this.ship.getData('slowSpeed'));
        }

        // Show flag when all survivors collected
        if (this.survivorsCollected === this.totalSurvivors) {
            this.flag.setVisible(true);
            this.flag.setData('appeared', true);
            this.showMessage('All survivors rescued! Reach the flag!');
        }
    }

    loseLife() {
        // Implement cooldown to prevent multiple life losses at once
        if (this.lastLifeLost && Date.now() - this.lastLifeLost < 2000) {
            return;
        }

        this.lastLifeLost = Date.now();
        this.lives--;
        this.livesText.setText('Lives: ' + this.lives);

        if (this.lives <= 0) {
            this.loseGame();
        } else {
            // Reset ship position
            this.ship.x = 512;
            this.ship.y = 650;
            this.showMessage('Hit by wave! Lives remaining: ' + this.lives, 1500);
        }
    }

    updateTimer() {
        if (this.gameStarted && !this.gameWon && !this.gameLost) {
            this.gameTime++;
            this.timerText.setText('Time: ' + this.gameTime + 's');
        }
    }

    winGame() {
        this.gameWon = true;
        this.gameStarted = false;

        this.instructionsText.setVisible(true);
        this.instructionsText.setText(
            'MISSION COMPLETE!\n\n' +
            'All survivors rescued!\n' +
            'Score: ' + this.score + '\n' +
            'Time: ' + this.gameTime + ' seconds\n\n' +
            'Press SPACE to play again'
        );
    }

    loseGame() {
        this.gameLost = true;
        this.gameStarted = false;

        this.instructionsText.setVisible(true);
        this.instructionsText.setText(
            'MISSION FAILED\n\n' +
            'You ran out of lives!\n' +
            'Survivors rescued: ' + this.survivorsCollected + '/' + this.totalSurvivors + '\n' +
            'Time survived: ' + this.gameTime + ' seconds\n\n' +
            'Press SPACE to try again'
        );
    }

    showMessage(text, duration = 2000) {
        const message = this.add.text(512, 384, text, {
            font: '24px Arial',
            fill: '#ffffff',
            backgroundColor: '#000000',
            padding: { x: 20, y: 10 },
            align: 'center'
        });
        message.setOrigin(0.5);

        this.time.delayedCall(duration, () => {
            message.destroy();
        });
    }

    restartGame() {
        this.scene.restart();
    }
}

// Phaser game configuration
const config = {
    type: Phaser.AUTO,
    width: 1024,
    height: 768,
    parent: 'game-container',
    backgroundColor: '#1A80B6',
    scene: GameScene,
    physics: {
        default: 'arcade',
        arcade: {
            debug: false
        }
    }
};

// Create the game instance
const game = new Phaser.Game(config);
