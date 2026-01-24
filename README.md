# Sentinel-C v3.10 🛡️

**Author:** Voltsparx  
**Contact:** voltsparx@gmail.com  
**Language:** C/C++  
**Repo:** [https://github.com/voltsparx/Sentinel-C](https://github.com/voltsparx/Sentinel-C)  

Sentinel-C is an **Advanced Host Defense Multi-Tool**.  
It provides file integrity monitoring, logging, HTML reports, and additional small security utilities — designed for cybersecurity learners, professionals, and anyone who cares about system security.

---

## ⚠️ **Ethical Use & Disclaimer**

- This tool is **only for ethical monitoring** of systems and directories you own or have permission to monitor.  
- **Do not** use it to tamper with, spy on, or attack systems you do not own.  
- The author is **not responsible for misuse**.  
- Data logged by Sentinel-C is stored locally for your convenience and **not shared anywhere**.

---

## 🛠️ **Installation**

### **Linux / Unix:**

```bash
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C
mkdir build
cd build
cmake ..
cmake --build .
```

#### Run from build folder:

```bash
./sentinel-c --help
```

Optional: Add to PATH for global use:

```bash
sudo cp sentinel-c /usr/local/bin/
```

### **Windows (CMD / PowerShell):**

```powershell
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C
mkdir build
cd build
cmake ..
cmake --build .
```

#### Run executable:

```powershell
sentinel-c.exe --help
```

---

## 📁 **Project Structure**

```
Sentinel-C/
├── src/                # Source & headers
├── CMakeLists.txt
├── README.md
├── .gitignore
├── sentinel-c-logs/    # Logs & HTML reports
│   ├── data/
│   └── reports/
```

- Folders `data/` and `reports/` are **automatically created** if missing.  
- `.sentinel.log` is stored in `data/`.  
- HTML reports are stored in `reports/`.

---

## ⚡ **Features**

- Multi-tool framework for daily security and monitoring.  
- File integrity monitoring (NEW, MODIFIED, DELETED files).  
- SHA-256 based hashing for file verification.  
- Continuous monitoring with customizable intervals.  
- Logs actions in **HTML reports** and local log files.  
- Baseline integrity verification (`--doctor`).  
- Single file verification (`--verify`).  
- Banner display and tool information (`--banner`, `--about`).  
- Compatible with **Linux and Windows**.  
- Beginner-friendly CLI with short (`-`) and long (`--`) commands.

---

## 💻 **Commands & Usage**

<table>
  <thead>
    <tr>
      <th>Command</th>
      <th>Short</th>
      <th>Description</th>
      <th>Example</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Show help</td>
      <td>-h</td>
      <td>Display this help menu</td>
      <td><code>sentinel-c --help</code></td>
    </tr>
    <tr>
      <td>Version</td>
      <td>-v</td>
      <td>Show tool version</td>
      <td><code>sentinel-c --version</code></td>
    </tr>
    <tr>
      <td>Show banner</td>
      <td>–</td>
      <td>Display ASCII banner</td>
      <td><code>sentinel-c --banner</code></td>
    </tr>
    <tr>
      <td>About</td>
      <td>–</td>
      <td>Tool info + author contact</td>
      <td><code>sentinel-c --about</code></td>
    </tr>
    <tr>
      <td>Initialize baseline</td>
      <td>-i</td>
      <td>Scan directory and create baseline</td>
      <td><code>sentinel-c --init ./myfolder</code></td>
    </tr>
    <tr>
      <td>Scan</td>
      <td>-s</td>
      <td>Compare current directory to baseline</td>
      <td><code>sentinel-c --scan ./myfolder</code></td>
    </tr>
    <tr>
      <td>Monitor</td>
      <td>-m</td>
      <td>Continuously scan every N seconds</td>
      <td><code>sentinel-c --monitor ./myfolder 10</code></td>
    </tr>
    <tr>
      <td>Verify file</td>
      <td>-f</td>
      <td>Check SHA-256 hash of a single file</td>
      <td><code>sentinel-c --verify ./file.txt</code></td>
    </tr>
    <tr>
      <td>Doctor</td>
      <td>-d</td>
      <td>Check baseline integrity</td>
      <td><code>sentinel-c --doctor</code></td>
    </tr>
  </tbody>
</table>


---

## 📌 **Multi-Option Example**

```bash
# Initialize baseline and then scan directory
sentinel-c --init ./myfolder
sentinel-c --scan ./myfolder

# Monitor a directory every 15 seconds
sentinel-c --monitor ./myfolder 15

# Verify a single file
sentinel-c --verify ./myfolder/file.txt

# Check baseline integrity
sentinel-c --doctor

# Show tool info with contact
sentinel-c --about
```

---

## 🟢 **Output**

- Colored terminal messages:  
  - **Green** → NEW files  
  - **Yellow** → MODIFIED files  
  - **Red** → DELETED files  

- Logs: `sentinel-c-logs/data/.sentinel.log`  
- HTML reports: `sentinel-c-logs/reports/sentinel_report_<timestamp>.html`

---

## ⭐ **Contribution**

- Fork and add features freely.  
- Follow ethical security guidelines.  

---

## 📄 **License**

MIT License
