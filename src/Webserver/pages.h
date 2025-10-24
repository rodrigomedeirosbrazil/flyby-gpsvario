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

#endif

