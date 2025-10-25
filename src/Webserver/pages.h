#ifndef WEBSERVER_PAGES_H
#define WEBSERVER_PAGES_H

// CSS styles shared across all pages
const char HTML_STYLE[] PROGMEM = R"rawliteral(
<style>
body {
    font-family: Arial, sans-serif;
    max-width: 600px;
    margin: 0 auto;
    padding: 20px;
    background-color: #f0f0f0;
}
.container {
    background-color: white;
    border-radius: 10px;
    padding: 20px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}
h1 {
    color: #333;
    text-align: center;
    border-bottom: 3px solid #4CAF50;
    padding-bottom: 10px;
}
.menu {
    list-style: none;
    padding: 0;
    margin: 20px 0;
}
.menu li {
    margin: 10px 0;
}
.menu a, .btn {
    display: block;
    padding: 15px;
    background-color: #4CAF50;
    color: white;
    text-decoration: none;
    border-radius: 5px;
    text-align: center;
    transition: background-color 0.3s;
}
.menu a:hover, .btn:hover {
    background-color: #45a049;
}
.info {
    background-color: #e3f2fd;
    padding: 15px;
    border-radius: 5px;
    margin: 20px 0;
    text-align: center;
}
.progress-container {
    width: 100%;
    background-color: #ddd;
    border-radius: 5px;
    margin: 20px 0;
    display: none;
}
.progress-bar {
    width: 0%;
    height: 30px;
    background-color: #4CAF50;
    border-radius: 5px;
    text-align: center;
    line-height: 30px;
    color: white;
    transition: width 0.3s;
}
.file-input {
    margin: 20px 0;
    padding: 10px;
    border: 2px dashed #4CAF50;
    border-radius: 5px;
    text-align: center;
}
input[type="file"] {
    margin: 10px 0;
}
.btn {
    cursor: pointer;
    border: none;
    font-size: 16px;
}
.btn:disabled {
    background-color: #ccc;
    cursor: not-allowed;
}
.message {
    padding: 15px;
    margin: 10px 0;
    border-radius: 5px;
    display: none;
}
.message.success {
    background-color: #d4edda;
    color: #155724;
    display: block;
}
.message.error {
    background-color: #f8d7da;
    color: #721c24;
    display: block;
}
.timer {
    font-size: 24px;
    color: #ff5722;
    font-weight: bold;
}
.form-group {
    margin: 15px 0;
}
.form-group label {
    display: block;
    margin-bottom: 5px;
    font-weight: bold;
    color: #333;
}
.form-group input, .form-group select {
    width: 100%;
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 16px;
    box-sizing: border-box;
}
.form-group input[type="checkbox"] {
    width: auto;
    margin-right: 10px;
}
.form-group label input[type="checkbox"] {
    display: inline;
    width: auto;
}
</style>
)rawliteral";

// Home page
const char HTML_HOME[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Flyby GPS Vario</title>
<style>
body {
    font-family: Arial, sans-serif;
    max-width: 600px;
    margin: 0 auto;
    padding: 20px;
    background-color: #f0f0f0;
}
.container {
    background-color: white;
    border-radius: 10px;
    padding: 20px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}
h1 {
    color: #333;
    text-align: center;
    border-bottom: 3px solid #4CAF50;
    padding-bottom: 10px;
}
.menu {
    list-style: none;
    padding: 0;
    margin: 20px 0;
}
.menu li {
    margin: 10px 0;
}
.menu a, .btn {
    display: block;
    padding: 15px;
    background-color: #4CAF50;
    color: white;
    text-decoration: none;
    border-radius: 5px;
    text-align: center;
    transition: background-color 0.3s;
}
.menu a:hover, .btn:hover {
    background-color: #45a049;
}
</style>
</head>
<body>
    <div class="container">
        <h1>FLYBY GPS VARIO</h1>
        <ul class="menu">
            <li><a href="/ota">OTA Firmware Update</a></li>
            <li><a href="/config">⚙️ Configuration</a></li>
            <li><a href="/info">Device Information</a></li>
        </ul>
    </div>
</body>
</html>
)rawliteral";

// OTA Update page
const char HTML_OTA[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OTA Update - Flyby GPS Vario</title>
<style>
body {
    font-family: Arial, sans-serif;
    max-width: 600px;
    margin: 0 auto;
    padding: 20px;
    background-color: #f0f0f0;
}
.container {
    background-color: white;
    border-radius: 10px;
    padding: 20px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}
h1 {
    color: #333;
    text-align: center;
    border-bottom: 3px solid #4CAF50;
    padding-bottom: 10px;
}
.btn {
    display: block;
    padding: 15px;
    background-color: #4CAF50;
    color: white;
    text-decoration: none;
    border-radius: 5px;
    text-align: center;
    transition: background-color 0.3s;
    cursor: pointer;
    border: none;
    font-size: 16px;
}
.btn:hover {
    background-color: #45a049;
}
.btn:disabled {
    background-color: #ccc;
    cursor: not-allowed;
}
.progress-container {
    width: 100%;
    background-color: #ddd;
    border-radius: 5px;
    margin: 20px 0;
    display: none;
}
.progress-bar {
    width: 0%;
    height: 30px;
    background-color: #4CAF50;
    border-radius: 5px;
    text-align: center;
    line-height: 30px;
    color: white;
    transition: width 0.3s;
}
.file-input {
    margin: 20px 0;
    padding: 10px;
    border: 2px dashed #4CAF50;
    border-radius: 5px;
    text-align: center;
}
input[type="file"] {
    margin: 10px 0;
}
.message {
    padding: 15px;
    margin: 10px 0;
    border-radius: 5px;
    display: none;
}
.message.success {
    background-color: #d4edda;
    color: #155724;
    display: block;
}
.message.error {
    background-color: #f8d7da;
    color: #721c24;
    display: block;
}
</style>
</head>
<body>
    <div class="container">
        <h1>OTA FIRMWARE UPDATE</h1>

        <div class="file-input">
            <p>Select firmware file (.bin)</p>
            <input type="file" id="fileInput" accept=".bin">
        </div>

        <button class="btn" id="uploadBtn" onclick="uploadFile()" disabled>Upload Firmware</button>

        <div class="progress-container" id="progressContainer">
            <div class="progress-bar" id="progressBar">0%</div>
        </div>

        <div class="message" id="message"></div>

        <div style="margin-top: 20px;">
            <a href="/" style="color: #4CAF50; text-decoration: none;">← Back to Home</a>
        </div>
    </div>

    <script>
        var fileInput = document.getElementById('fileInput');
        var uploadBtn = document.getElementById('uploadBtn');
        var progressContainer = document.getElementById('progressContainer');
        var progressBar = document.getElementById('progressBar');
        var message = document.getElementById('message');

        fileInput.addEventListener('change', function() {
            uploadBtn.disabled = !fileInput.files.length;
        });

        function uploadFile() {
            var file = fileInput.files[0];
            if (!file) {
                showMessage('Please select a file', 'error');
                return;
            }

            if (!file.name.endsWith('.bin')) {
                showMessage('Please select a .bin file', 'error');
                return;
            }

            uploadBtn.disabled = true;
            fileInput.disabled = true;
            progressContainer.style.display = 'block';
            message.style.display = 'none';

            var formData = new FormData();
            formData.append('file', file);

            var xhr = new XMLHttpRequest();

            xhr.upload.addEventListener('progress', function(e) {
                if (e.lengthComputable) {
                    var percentComplete = (e.loaded / e.total) * 100;
                    progressBar.style.width = percentComplete + '%';
                    progressBar.textContent = Math.round(percentComplete) + '%';
                }
            });

            xhr.addEventListener('load', function() {
                if (xhr.status === 200) {
                    progressBar.style.width = '100%';
                    progressBar.textContent = '100%';
                    showMessage('Update successful! Device rebooting...', 'success');
                    setTimeout(function() {
                        window.location.href = '/';
                    }, 5000);
                } else {
                    showMessage('Update failed: ' + xhr.statusText, 'error');
                    uploadBtn.disabled = false;
                    fileInput.disabled = false;
                }
            });

            xhr.addEventListener('error', function() {
                showMessage('Upload error occurred', 'error');
                uploadBtn.disabled = false;
                fileInput.disabled = false;
            });

            xhr.open('POST', '/ota/upload');
            xhr.send(formData);
        }

        function showMessage(text, type) {
            message.textContent = text;
            message.className = 'message ' + type;
        }
    </script>
</body>
</html>
)rawliteral";

// Configuration page HTML
const char HTML_CONFIG_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Flyby GPS Vario - Configuration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="UTF-8">
)rawliteral" R"rawliteral(
</head>
<body>
    <div class="container">
        <h1>⚙️ Configuration</h1>
        
        <div class="info">
            <strong>Configure your Flyby GPS Vario settings</strong><br>
            Changes are saved automatically to device memory.
        </div>

        <form id="configForm">
            <div class="form-group">
                <label for="timezone">Timezone (UTC offset):</label>
                <select id="timezone" name="timezone">
                    <option value="-12">UTC-12</option>
                    <option value="-11">UTC-11</option>
                    <option value="-10">UTC-10</option>
                    <option value="-9">UTC-9</option>
                    <option value="-8">UTC-8</option>
                    <option value="-7">UTC-7</option>
                    <option value="-6">UTC-6</option>
                    <option value="-5">UTC-5</option>
                    <option value="-4">UTC-4</option>
                    <option value="-3">UTC-3</option>
                    <option value="-2">UTC-2</option>
                    <option value="-1">UTC-1</option>
                    <option value="0">UTC+0</option>
                    <option value="1">UTC+1</option>
                    <option value="2">UTC+2</option>
                    <option value="3">UTC+3</option>
                    <option value="4">UTC+4</option>
                    <option value="5">UTC+5</option>
                    <option value="6">UTC+6</option>
                    <option value="7">UTC+7</option>
                    <option value="8">UTC+8</option>
                    <option value="9">UTC+9</option>
                    <option value="10">UTC+10</option>
                    <option value="11">UTC+11</option>
                    <option value="12">UTC+12</option>
                    <option value="13">UTC+13</option>
                    <option value="14">UTC+14</option>
                </select>
            </div>

            <div class="form-group">
                <label for="takeoffSpeed">Takeoff Speed (km/h):</label>
                <input type="number" id="takeoffSpeed" name="takeoffSpeed" min="3" max="15" step="1">
            </div>

            <div class="form-group">
                <label for="pdopMaxThreshold">GPS PDOP Max Threshold:</label>
                <input type="number" id="pdopMaxThreshold" name="pdopMaxThreshold" min="50" max="1000" step="10">
            </div>

            <div class="form-group">
                <label for="qnh">QNH Pressure (Pa):</label>
                <input type="number" id="qnh" name="qnh" min="95000" max="105000" step="100">
            </div>

            <div class="form-group">
                <label>
                    <input type="checkbox" id="qnhByGps" name="qnhByGps">
                    Auto-adjust QNH by GPS altitude
                </label>
            </div>

            <div class="form-group">
                <label>
                    <input type="checkbox" id="varioBeepOnlyInFlight" name="varioBeepOnlyInFlight">
                    Vario beep only when in flight
                </label>
            </div>

            <div class="form-group">
                <label for="climbRate">Climb Rate Threshold (m/s):</label>
                <input type="number" id="climbRate" name="climbRate" min="0" max="5" step="0.1">
            </div>

            <div class="form-group">
                <label for="sinkRate">Sink Rate Threshold (m/s):</label>
                <input type="number" id="sinkRate" name="sinkRate" min="-10" max="0" step="0.1">
            </div>

            <div class="form-group">
                <button type="submit" class="btn">💾 Save Configuration</button>
                <button type="button" class="btn" onclick="loadDefaults()" style="background-color: #ff9800;">🔄 Reset to Defaults</button>
            </div>
        </form>

        <div id="message" class="message" style="display: none;"></div>

        <div class="menu">
            <a href="/">🏠 Home</a>
            <a href="/ota">📤 OTA Update</a>
            <a href="/info">📊 Device Info</a>
        </div>
    </div>

    <script>
        // Load current configuration
        function loadConfig() {
            fetch('/api/config')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('timezone').value = data.timezone;
                    document.getElementById('takeoffSpeed').value = data.takeoffSpeed;
                    document.getElementById('pdopMaxThreshold').value = data.pdopMaxThreshold;
                    document.getElementById('qnh').value = data.qnh;
                    document.getElementById('qnhByGps').checked = data.qnhByGps;
                    document.getElementById('varioBeepOnlyInFlight').checked = data.varioBeepOnlyInFlight;
                    document.getElementById('climbRate').value = data.climbRate;
                    document.getElementById('sinkRate').value = data.sinkRate;
                })
                .catch(error => {
                    showMessage('Failed to load configuration', 'error');
                });
        }

        // Save configuration
        document.getElementById('configForm').addEventListener('submit', function(e) {
            e.preventDefault();
            
            const formData = new FormData(this);
            const config = {};
            
            for (let [key, value] of formData.entries()) {
                if (key === 'qnhByGps' || key === 'varioBeepOnlyInFlight') {
                    config[key] = true;
                } else {
                    config[key] = parseFloat(value);
                }
            }
            
            // Handle checkboxes separately
            config.qnhByGps = document.getElementById('qnhByGps').checked;
            config.varioBeepOnlyInFlight = document.getElementById('varioBeepOnlyInFlight').checked;

            fetch('/api/config', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(config)
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    showMessage('Configuration saved successfully!', 'success');
                } else {
                    showMessage('Failed to save configuration: ' + data.error, 'error');
                }
            })
            .catch(error => {
                showMessage('Error saving configuration', 'error');
            });
        });

        // Load defaults
        function loadDefaults() {
            if (confirm('Are you sure you want to reset all settings to defaults?')) {
                fetch('/api/config/defaults', {
                    method: 'POST'
                })
                .then(response => response.json())
                .then(data => {
                    if (data.success) {
                        showMessage('Configuration reset to defaults!', 'success');
                        loadConfig(); // Reload the form
                    } else {
                        showMessage('Failed to reset configuration', 'error');
                    }
                })
                .catch(error => {
                    showMessage('Error resetting configuration', 'error');
                });
            }
        }

        function showMessage(text, type) {
            const message = document.getElementById('message');
            message.textContent = text;
            message.className = 'message ' + type;
            message.style.display = 'block';
            
            setTimeout(() => {
                message.style.display = 'none';
            }, 3000);
        }

        // Load configuration when page loads
        loadConfig();
    </script>
</body>
</html>
)rawliteral";

#endif

