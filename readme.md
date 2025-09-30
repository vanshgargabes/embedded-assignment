# W-MBus AES-128 Decryption (OMS Volume 2)

## 📌 Overview
This project implements *AES-128 decryption* of a Wireless M-Bus telegram according to the *OMS (Open Metering System) Volume 2 specification*.  
It demonstrates handling of encrypted smart meter messages by extracting the Initialization Vector (IV) and performing AES-128 decryption to recover the payload.  

This assignment showcases skills in *embedded systems development, cryptography, and C++ implementation*.

---

## ⚙ Dependencies
- *C++17* or later  
- *OpenSSL (libcrypto)* for AES-128 decryption  
- *Make* build system  

Install dependencies on Linux:
```bash
sudo apt-get update
sudo apt-get install g++ make libssl-dev
