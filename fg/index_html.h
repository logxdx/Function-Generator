#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char* index_html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Wave Generator</title>
  <style>
:root {
  --primary: #3498db;
  --primary-dark: #2980b9;
  --secondary: #2ecc71;
  --secondary-dark: #27ae60;
  --danger: #e74c3c;
  --danger-dark: #c0392b;
  --text: #34495e;
  --background: #f5f7fa;
  --card: #ffffff;
  --border: #e0e0e0;
  --shadow: rgba(0, 0, 0, 0.1);
}

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background-color: var(--background);
      color: var(--text);
      line-height: 1.6;
      padding: 0;
      margin: 0;
      min-height: 100vh;
    }

    .container {
      width: 100%;
      max-width: 800px;
      margin: 0 auto;
      padding: 20px;
    }

    header {
      background: linear-gradient(135deg, var(--primary), var(--primary-dark));
      color: white;
      padding: 20px;
      text-align: center;
      border-radius: 10px 10px 0 0;
      margin-bottom: 20px;
      box-shadow: 0 4px 6px var(--shadow);
    }

    header h1 {
      margin: 0;
      font-weight: 600;
      font-size: clamp(20px, 5vw, 28px);
    }

    header p {
      margin-top: 10px;
      opacity: 0.9;
      font-size: clamp(14px, 3vw, 16px);
    }

    .card {
      background-color: var(--card);
      border-radius: 10px;
      box-shadow: 0 4px 6px var(--shadow);
      padding: clamp(15px, 5vw, 25px);
      margin-bottom: 20px;
      width: 100%;
    }

    .control-group {
      margin-bottom: 20px;
      width: 100%;
    }

    .control-group:last-child {
      margin-bottom: 0;
    }

    .control-label {
      display: block;
      margin-bottom: 10px;
      font-weight: 600;
      color: var(--text);
      font-size: clamp(14px, 3vw, 16px);
    }

    .control-actions {
      display: flex;
      gap: 10px;
      margin-bottom: 20px;
      flex-wrap: wrap;
    }

    button {
      padding: clamp(10px, 3vw, 12px) clamp(15px, 5vw, 20px);
      border: none;
      border-radius: 5px;
      font-size: clamp(14px, 3vw, 16px);
      font-weight: 600;
      cursor: pointer;
      transition: all 0.3s ease;
      box-shadow: 0 2px 4px var(--shadow);
      flex: 1;
      min-width: 120px;
    }

    .btn-primary {
      background-color: var(--primary);
      color: white;
    }

    .btn-primary:hover {
      background-color: var(--primary-dark);
      transform: translateY(-2px);
    }

    .btn-danger {
      background-color: var(--danger);
      color: white;
    }

    .btn-danger:hover {
      background-color: var(--danger-dark);
      transform: translateY(-2px);
    }

    input[type="number"],
    select {
      width: 100%;
      padding: clamp(8px, 2vw, 12px);
      border: 1px solid var(--border);
      border-radius: 5px;
      font-size: clamp(14px, 3vw, 16px);
      background-color: white;
      transition: border 0.3s;
    }

    input[type="number"]:focus,
    select:focus {
      outline: none;
      border-color: var(--primary);
      box-shadow: 0 0 0 3px rgba(52, 152, 219, 0.2);
    }

    .slider-container {
      display: flex;
      align-items: center;
      margin-top: 10px;
      gap: 15px;
      flex-wrap: wrap;
    }

    .slider {
      flex-grow: 1;
      height: 8px;
      -webkit-appearance: none;
      appearance: none;
      background: #dcdde1;
      outline: none;
      border-radius: 4px;
      min-width: 150px;
      width: 100%;
    }

    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 20px;
      height: 20px;
      border-radius: 50%;
      background: var(--primary);
      cursor: pointer;
      transition: all 0.2s;
    }

    .slider::-webkit-slider-thumb:hover {
      transform: scale(1.1);
      background: var(--primary-dark);
    }

    .slider::-moz-range-thumb {
      width: 20px;
      height: 20px;
      border: none;
      border-radius: 50%;
      background: var(--primary);
      cursor: pointer;
      transition: all 0.2s;
    }

    .slider::-moz-range-thumb:hover {
      transform: scale(1.1);
      background: var(--primary-dark);
    }

    .number-input {
      flex: 0 0 80px;
      max-width: 100px;
    }

    .wave-icon {
      width: 40px;
      height: 40px;
      margin-right: 10px;
      vertical-align: middle;
      flex-shrink: 0;
    }

    .wave-option {
      display: flex;
      align-items: center;
      padding: 10px;
      margin-bottom: 0;
      border: 2px solid var(--border);
      border-radius: 5px;
      cursor: pointer;
      transition: all 0.3s;
      height: 100%;
    }

    .wave-option:hover {
      background-color: rgba(52, 152, 219, 0.1);
    }

    .wave-option.selected {
      background-color: rgba(52, 152, 219, 0.2);
      border-color: var(--primary);
    }

    .wave-label {
      font-weight: 500;
      font-size: clamp(13px, 2.5vw, 15px);
    }

    .wave-options {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
      gap: 15px;
      margin-top: 10px;
      width: 100%;
    }

    .status-indicator {
      display: inline-block;
      width: 12px;
      height: 12px;
      background-color: #e74c3c;
      border-radius: 50%;
      margin-right: 8px;
      flex-shrink: 0;
    }

    .status-indicator.active {
      background-color: #2ecc71;
    }

    .status-text {
      font-size: clamp(13px, 2.5vw, 14px);
      margin-top: 10px;
      display: flex;
      align-items: center;
    }

    footer {
      text-align: center;
      margin-top: 30px;
      color: #7f8c8d;
      font-size: clamp(12px, 2.5vw, 14px);
      padding: 15px;
    }

    @media (max-width: 600px) {
      .control-actions {
        flex-direction: column;
      }
      
      button {
        width: 100%;
      }
      
      .slider-container {
        flex-direction: column;
        align-items: stretch;
      }
      
      .number-input {
        max-width: none;
        width: 100%;
        flex: none;
      }

      .wave-options {
        grid-template-columns: 1fr 1fr;
      }
    }

    @media (max-width: 400px) {
      .wave-options {
        grid-template-columns: 1fr;
      }
    }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <h1>ESP32 Wave Generator</h1>
      <p>Control and customize signal waveforms with precision</p>
    </header>

    <div class="card">
      <div class="status-text">
        <span id="statusIndicator" class="status-indicator"></span>
        <span id="statusText">Generator stopped</span>
      </div>
      
      <div class="control-actions">
        <button id="startBtn" class="btn-primary" onclick="startWave()">Start Wave</button>
        <button id="stopBtn" class="btn-danger" onclick="stopWave()">Stop Wave</button>
      </div>
    </div>

    <div class="card">
      <div class="control-group">
        <label class="control-label" for="freqSlider">Frequency (Hz)</label>
        <div class="slider-container">
          <input type="range" id="freqSlider" class="slider" min="0.1" max="2000000" value="1000" step="1">
          <input type="number" id="freqNumber" class="number-input" min="0.1" max="2000000" value="1000" step="1">
        </div>
      </div>
    </div>

    <div class="card">
      <div class="control-group">
        <span class="control-label">Waveform</span>
        <div class="wave-options">
          <div class="wave-option selected" data-value="0" onclick="selectWave(this, 0)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,20 C10,5 20,35 30,20 C40,5 50,35 60,20 C70,5 80,35 90,20 L100,20" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Sine</span>
          </div>
          <div class="wave-option" data-value="1" onclick="selectWave(this, 1)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,20 L0,5 L50,5 L50,35 L100,35" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Square1</span>
          </div>
          <div class="wave-option" data-value="2" onclick="selectWave(this, 2)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,35 L25,35 L25,5 L75,5 L75,35 L100,35" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Square2</span>
          </div>
          <div class="wave-option" data-value="3" onclick="selectWave(this, 3)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,35 L25,5 L75,35 L100,5" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Triangle</span>
          </div>
        </div>
      </div>
    </div>

    <div class="card">
      <div class="control-group">
        <label class="control-label" for="ampSlider">Amplitude (V)</label>
        <div class="slider-container">
          <input type="range" id="ampSlider" class="slider" min="0" max="12" value="3" step="0.1">
          <input type="number" id="ampNumber" class="number-input" min="0" max="12" value="3" step="0.1">
        </div>
      </div>

      <div class="control-group">
        <label class="control-label" for="offsetSlider">Offset (V)</label>
        <div class="slider-container">
          <input type="range" id="offsetSlider" class="slider" min="-12" max="12" value="0" step="0.1">
          <input type="number" id="offsetNumber" class="number-input" min="-12" max="12" value="0" step="0.1">
        </div>
      </div>
    </div>

    <footer>
      ESP32 Wave Generator &copy; 2025 | Hardware Interface
    </footer>
  </div>

  <script>
    // State variables
    let isRunning = false;
    let currentWave = 0;
    
    // Initialize components
    const freqSlider = document.getElementById('freqSlider');
    const freqNumber = document.getElementById('freqNumber');
    const ampSlider = document.getElementById('ampSlider');
    const ampNumber = document.getElementById('ampNumber');
    const offsetSlider = document.getElementById('offsetSlider');
    const offsetNumber = document.getElementById('offsetNumber');
    const statusIndicator = document.getElementById('statusIndicator');
    const statusText = document.getElementById('statusText');
    
    // Link sliders and number inputs
    freqSlider.addEventListener('input', () => {
      freqNumber.value = freqSlider.value;
      updateFreq(freqSlider.value);
    });
    
    freqNumber.addEventListener('input', () => {
      freqSlider.value = freqNumber.value;
      updateFreq(freqNumber.value);
    });
    
    ampSlider.addEventListener('input', () => {
      ampNumber.value = ampSlider.value;
      updateAmp(ampSlider.value);
    });
    
    ampNumber.addEventListener('input', () => {
      ampSlider.value = ampNumber.value;
      updateAmp(ampNumber.value);
    });
    
    offsetSlider.addEventListener('input', () => {
      offsetNumber.value = offsetSlider.value;
      updateOffset(offsetSlider.value);
    });
    
    offsetNumber.addEventListener('input', () => {
      offsetSlider.value = offsetNumber.value;
      updateOffset(offsetNumber.value);
    });
    
    // Handle touch events for better mobile experience
    freqSlider.addEventListener('touchstart', function(e) {
      e.stopPropagation();
    });
    
    ampSlider.addEventListener('touchstart', function(e) {
      e.stopPropagation();
    });
    
    offsetSlider.addEventListener('touchstart', function(e) {
      e.stopPropagation();
    });
    
    // Wave generator functions
    function startWave() {
      fetch('/start')
        .then(() => {
          isRunning = true;
          updateStatus();
        })
        .catch(error => console.error('Error starting wave:', error));
    }
    
    function stopWave() {
      fetch('/stop')
        .then(() => {
          isRunning = false;
          updateStatus();
        })
        .catch(error => console.error('Error stopping wave:', error));
    }
    
    function updateFreq(val) {
      fetch('/set_freq?val=' + val)
        .catch(error => console.error('Error updating frequency:', error));
    }
    
    function selectWave(element, val) {
      // Update UI
      document.querySelectorAll('.wave-option').forEach(el => {
        el.classList.remove('selected');
      });
      element.classList.add('selected');
      
      // Update server
      currentWave = val;
      setWave(val);
    }
    
    function setWave(val) {
      fetch('/set_wave?type=' + val)
        .catch(error => console.error('Error setting wave type:', error));
    }
    
    function updateAmp(val) {
      fetch('/set_amp?val=' + val)
        .catch(error => console.error('Error updating amplitude:', error));
    }
    
    function updateOffset(val) {
      fetch('/set_offset?val=' + val)
        .catch(error => console.error('Error updating offset:', error));
    }
    
    function updateStatus() {
      if (isRunning) {
        statusIndicator.classList.add('active');
        statusText.textContent = "Generator running";
      } else {
        statusIndicator.classList.remove('active');
        statusText.textContent = "Generator stopped";
      }
    }
    
    // Check for mobile/touch devices
    function isTouchDevice() {
      return ('ontouchstart' in window) || (navigator.maxTouchPoints > 0) || (navigator.msMaxTouchPoints > 0);
    }
    
    // Add touch-friendly class if needed
    if (isTouchDevice()) {
      document.body.classList.add('touch-device');
    }
    
    // Initialize status
    updateStatus();
  </script>
</body>
</html>
)rawliteral";

const char* index_html1 = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Wave Generator</title>
  <style>
    :root {
      --primary: #3498db;
      --primary-dark: #2980b9;
      --secondary: #2ecc71;
      --secondary-dark: #27ae60;
      --danger: #e74c3c;
      --danger-dark: #c0392b;
      --text: #34495e;
      --background: #f5f7fa;
      --card: #ffffff;
      --border: #e0e0e0;
      --shadow: rgba(0, 0, 0, 0.1);
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background-color: var(--background);
      color: var(--text);
      line-height: 1.6;
      padding: 0;
      margin: 0;
      min-height: 100vh;
    }

    .container {
      width: 100%;
      max-width: 800px;
      margin: 0 auto;
      padding: 20px;
    }

    header {
      background: linear-gradient(135deg, var(--primary), var(--primary-dark));
      color: white;
      padding: 20px;
      text-align: center;
      border-radius: 10px 10px 0 0;
      margin-bottom: 20px;
      box-shadow: 0 4px 6px var(--shadow);
    }

    header h1 {
      margin: 0;
      font-weight: 600;
      font-size: clamp(20px, 5vw, 28px);
    }

    header p {
      margin-top: 10px;
      opacity: 0.9;
      font-size: clamp(14px, 3vw, 16px);
    }

    .card {
      background-color: var(--card);
      border-radius: 10px;
      box-shadow: 0 4px 6px var(--shadow);
      padding: clamp(15px, 5vw, 25px);
      margin-bottom: 20px;
      width: 100%;
    }

    .control-group {
      margin-bottom: 20px;
      width: 100%;
    }

    .control-group:last-child {
      margin-bottom: 0;
    }

    .control-label {
      display: block;
      margin-bottom: 10px;
      font-weight: 600;
      color: var(--text);
      font-size: clamp(14px, 3vw, 16px);
    }

    .control-actions {
      display: flex;
      gap: 10px;
      margin-bottom: 20px;
      flex-wrap: wrap;
    }

    button {
      padding: clamp(10px, 3vw, 12px) clamp(15px, 5vw, 20px);
      border: none;
      border-radius: 5px;
      font-size: clamp(14px, 3vw, 16px);
      font-weight: 600;
      cursor: pointer;
      transition: all 0.3s ease;
      box-shadow: 0 2px 4px var(--shadow);
      flex: 1;
      min-width: 120px;
    }

    .btn-primary {
      background-color: var(--primary);
      color: white;
    }

    .btn-primary:hover {
      background-color: var(--primary-dark);
      transform: translateY(-2px);
    }

    .btn-danger {
      background-color: var(--danger);
      color: white;
    }

    .btn-danger:hover {
      background-color: var(--danger-dark);
      transform: translateY(-2px);
    }

    input[type="number"],
    select {
      width: 100%;
      padding: clamp(8px, 2vw, 12px);
      border: 1px solid var(--border);
      border-radius: 5px;
      font-size: clamp(14px, 3vw, 16px);
      background-color: white;
      transition: border 0.3s;
    }

    input[type="number"]:focus,
    select:focus {
      outline: none;
      border-color: var(--primary);
      box-shadow: 0 0 0 3px rgba(52, 152, 219, 0.2);
    }

    .slider-container {
      display: flex;
      align-items: center;
      margin-top: 10px;
      gap: 15px;
      flex-wrap: wrap;
    }

    .slider {
      flex-grow: 1;
      height: 8px;
      -webkit-appearance: none;
      appearance: none;
      background: #dcdde1;
      outline: none;
      border-radius: 4px;
      min-width: 150px;
      width: 100%;
    }

    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 20px;
      height: 20px;
      border-radius: 50%;
      background: var(--primary);
      cursor: pointer;
      transition: all 0.2s;
    }

    .slider::-webkit-slider-thumb:hover {
      transform: scale(1.1);
      background: var(--primary-dark);
    }

    .slider::-moz-range-thumb {
      width: 20px;
      height: 20px;
      border: none;
      border-radius: 50%;
      background: var(--primary);
      cursor: pointer;
      transition: all 0.2s;
    }

    .slider::-moz-range-thumb:hover {
      transform: scale(1.1);
      background: var(--primary-dark);
    }

    .number-input {
      flex: 0 0 80px;
      max-width: 100px;
    }

    .wave-icon {
      width: 40px;
      height: 40px;
      margin-right: 10px;
      vertical-align: middle;
      flex-shrink: 0;
    }

    .wave-option {
      display: flex;
      align-items: center;
      padding: 10px;
      margin-bottom: 0;
      border: 2px solid var(--border);
      border-radius: 5px;
      cursor: pointer;
      transition: all 0.3s;
      height: 100%;
    }

    .wave-option:hover {
      background-color: rgba(52, 152, 219, 0.1);
    }

    .wave-option.selected {
      background-color: rgba(52, 152, 219, 0.2);
      border-color: var(--primary);
    }

    .wave-label {
      font-weight: 500;
      font-size: clamp(13px, 2.5vw, 15px);
    }

    .wave-options {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
      gap: 15px;
      margin-top: 10px;
      width: 100%;
    }

    .status-indicator {
      display: inline-block;
      width: 12px;
      height: 12px;
      background-color: #e74c3c;
      border-radius: 50%;
      margin-right: 8px;
      flex-shrink: 0;
    }

    .status-indicator.active {
      background-color: #2ecc71;
    }

    .status-text {
      font-size: clamp(13px, 2.5vw, 14px);
      margin-top: 10px;
      display: flex;
      align-items: center;
    }

    footer {
      text-align: center;
      margin-top: 30px;
      color: #7f8c8d;
      font-size: clamp(12px, 2.5vw, 14px);
      padding: 15px;
    }

    /* Additional styling for live amplitude and offset values */
    .value {
      font-size: 48px;
      font-weight: bold;
    }

    @media (max-width: 600px) {
      .control-actions {
        flex-direction: column;
      }
      
      button {
        width: 100%;
      }
      
      .slider-container {
        flex-direction: column;
        align-items: stretch;
      }
      
      .number-input {
        max-width: none;
        width: 100%;
        flex: none;
      }

      .wave-options {
        grid-template-columns: 1fr 1fr;
      }
    }

    @media (max-width: 400px) {
      .wave-options {
        grid-template-columns: 1fr;
      }
    }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <h1>ESP32 Wave Generator</h1>
      <p>Control and customize signal waveforms with precision</p>
    </header>

    <div class="card">
      <div class="status-text">
        <span id="statusIndicator" class="status-indicator"></span>
        <span id="statusText">Generator stopped</span>
      </div>
      
      <div class="control-actions">
        <button id="startBtn" class="btn-primary" onclick="startWave()">Start Wave</button>
        <button id="stopBtn" class="btn-danger" onclick="stopWave()">Stop Wave</button>
      </div>
    </div>

    <div class="card">
      <div class="control-group">
        <label class="control-label" for="freqSlider">Frequency (Hz)</label>
        <div class="slider-container">
          <input type="range" id="freqSlider" class="slider" min="0.1" max="2000000" value="1000" step="1">
          <input type="number" id="freqNumber" class="number-input" min="0.1" max="2000000" value="1000" step="1">
        </div>
      </div>
    </div>

    <div class="card">
      <div class="control-group">
        <span class="control-label">Waveform</span>
        <div class="wave-options">
          <div class="wave-option selected" data-value="0" onclick="selectWave(this, 0)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,20 C10,5 20,35 30,20 C40,5 50,35 60,20 C70,5 80,35 90,20 L100,20" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Sine</span>
          </div>
          <div class="wave-option" data-value="1" onclick="selectWave(this, 1)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,20 L0,5 L50,5 L50,35 L100,35" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Square1</span>
          </div>
          <div class="wave-option" data-value="2" onclick="selectWave(this, 2)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,35 L25,35 L25,5 L75,5 L75,35 L100,35" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Square2</span>
          </div>
          <div class="wave-option" data-value="3" onclick="selectWave(this, 3)">
            <svg class="wave-icon" viewBox="0 0 100 40" xmlns="http://www.w3.org/2000/svg">
              <path d="M0,35 L25,5 L75,35 L100,5" stroke="#3498db" stroke-width="3" fill="none"/>
            </svg>
            <span class="wave-label">Triangle</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Live Update Card for Amplitude and Offset -->
    <div class="card">
      <div class="control-group">
        <label class="control-label">Amplitude (V)</label>
        <div class="slider-container">
          <span id="amplitude" class="value">Loading...</span>
        </div>
      </div>

      <div class="control-group">
        <label class="control-label">Offset (V)</label>
        <div class="slider-container">
          <span id="offset" class="value">Loading...</span>
        </div>
      </div>
    </div>

    <footer>
      ESP32 Wave Generator &copy; 2025 | Hardware Interface
    </footer>
  </div>

  <script>
    // State variables
    let isRunning = false;
    let currentWave = 0;
    
    // Initialize components
    const freqSlider = document.getElementById('freqSlider');
    const freqNumber = document.getElementById('freqNumber');
    const statusIndicator = document.getElementById('statusIndicator');
    const statusText = document.getElementById('statusText');
    
    // Link frequency slider and number input
    freqSlider.addEventListener('input', () => {
      freqNumber.value = freqSlider.value;
      updateFreq(freqSlider.value);
    });
    
    freqNumber.addEventListener('input', () => {
      freqSlider.value = freqNumber.value;
      updateFreq(freqNumber.value);
    });
    
    // Wave generator functions
    function startWave() {
      fetch('/start')
        .then(() => {
          isRunning = true;
          updateStatus();
        })
        .catch(error => console.error('Error starting wave:', error));
    }
    
    function stopWave() {
      fetch('/stop')
        .then(() => {
          isRunning = false;
          updateStatus();
        })
        .catch(error => console.error('Error stopping wave:', error));
    }
    
    function updateFreq(val) {
      fetch('/set_freq?val=' + val)
        .catch(error => console.error('Error updating frequency:', error));
    }
    
    function selectWave(element, val) {
      // Update UI
      document.querySelectorAll('.wave-option').forEach(el => {
        el.classList.remove('selected');
      });
      element.classList.add('selected');
      
      // Update server
      currentWave = val;
      setWave(val);
    }
    
    function setWave(val) {
      fetch('/set_wave?type=' + val)
        .catch(error => console.error('Error setting wave type:', error));
    }
    
    function updateStatus() {
      if (isRunning) {
        statusIndicator.classList.add('active');
        statusText.textContent = "Generator running";
      } else {
        statusIndicator.classList.remove('active');
        statusText.textContent = "Generator stopped";
      }
    }
    
    // Function to fetch updated amplitude and offset values from the ESP32 endpoint
    function fetchValues() {
      fetch('/values')
        .then(response => response.json())
        .then(data => {
          document.getElementById('amplitude').textContent = data.amplitude;
          document.getElementById('offset').textContent = data.offset;
        })
        .catch(error => console.error('Error fetching data:', error));
    }
    
    window.onload = () => {
      fetchValues();
      setInterval(fetchValues, 100);
    };
    
    // Check for mobile/touch devices
    function isTouchDevice() {
      return ('ontouchstart' in window) || (navigator.maxTouchPoints > 0) || (navigator.msMaxTouchPoints > 0);
    }
    
    if (isTouchDevice()) {
      document.body.classList.add('touch-device');
    }
    
    // Initialize status
    updateStatus();
  </script>
</body>
</html>
)rawliteral";
#endif
