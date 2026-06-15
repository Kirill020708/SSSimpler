```
#!/bin/bash
echo "vm.nr_hugepages=128" | sudo tee -a /etc/sysctl.conf
sudo apt-get update
sudo apt-get install git python3 pip curl make g++ gcc htop git-lfs cmake clang llvm -y;
sudo apt-get install lld -y
wget https://packages.microsoft.com/config/debian/12/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
rm packages-microsoft-prod.deb
sudo apt-get update && sudo apt-get install -y dotnet-sdk-10.0
sudo curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs/ | sh

sudo source ~/.bashrc;

git clone https://github.com/rektdie/OpenBench
cd OpenBench/Client

sudo apt install python3-venv -y
sudo python3 -m venv myenv
sudo source myenv/bin/activate
sudo pip install -r requirements.txt --break-system-packages

touch run.sh
cat > run.sh << 'EOF'
#!/bin/bash

USERNAME="Kirill020708"
PASSWORD="KubikRubika"
SERVER_URL="https://rektdie.pythonanywhere.com/"
THREADS="4"
NODES="1"
IDENTITY="Dr. SPSA"

python3 client.py \
  -U "$USERNAME" \
  -P "$PASSWORD" \
  -S "$SERVER_URL" \
  -T "$THREADS" \
  -N "$NODES" \
  -I "$IDENTITY"
EOF

chmod +x run.sh
nohup ./run.sh &
```