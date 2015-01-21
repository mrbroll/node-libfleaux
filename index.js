var fleaux = null;

if (process.platform === 'linux') { //linux
    fleaux = require('./lib/linux/fleaux');
} else if (process.platform === 'darwin') { //macintosh
    fleaux = require('./lib/mac/fleaux');
} else if (process.platform === 'win32') { //windows
    fleaux = require('./lib/win/fleaux');
} else {
    fleaux = require('./build/Release/fleaux');
}

module.exports = fleaux;
