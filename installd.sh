#!/bin/bash
TEMP=/tmp/answer$$
whiptail --title "Astro [ASTRO]"  --menu  "Ubuntu 16.04/18.04 Daemon Node :" 20 0 0 1 "Compile astrod Ubuntu 16.04" 2 "Update astrod 16.04 to latest" 3 "Compile astrod Ubuntu 18.04" 4 "Update astrod 18.04 to latest" 2>$TEMP
choice=`cat $TEMP`
case $choice in
1) echo 1 "Compiling astrod Ubuntu 16.04"

echo "Updating linux packages"
sudo apt-get update -y && sudo apt-get upgrade -y

sudo apt-get --assume-yes install git unzip build-essential libssl-dev libdb++-dev libboost-all-dev libqrencode-dev libminiupnpc-dev libevent-dev obfs4proxy libcurl4-openssl-dev

echo "Installing Astro Wallet"
git clone https://github.com/equisde/Astro_Blockchain
cd Astro_Blockchain || exit
git checkout master
git pull

cd src
make -f makefile.unix

sudo yes | cp -rf astrod /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Populate astro.conf"
mkdir ~/.astro
echo -e "daemon=1\listen=1\rpcuser=user\rpcpassword=changethispassword" > ~/.astro/astro.conf


echo "Back to Compiled astrod Binary Folder"
cd ~/Astro_Blockchain/src
                ;;
2) echo 2 "Update astrod"
echo "Updating Astro Wallet"
cd ~/Astro_Blockchain || exit
git checkout master
git pull

cd src
make -f makefile.unix

sudo yes | cp -rf astrod /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Back to Compiled astrod Binary Folder"
cd ~/Astro_Blockchain/src
                ;;
3) echo 3 "Compile astrod Ubuntu 18.04"
echo "Updating linux packages"
sudo apt-get update -y && sudo apt-get upgrade -y

sudo apt-get --assume-yes install git unzip build-essential libdb++-dev libboost-all-dev libqrencode-dev libminiupnpc-dev libevent-dev obfs4proxy libssl-dev libcurl4-openssl-dev

echo "Downgrade libssl-dev"
sudo apt-get install make
wget https://www.openssl.org/source/openssl-1.0.1j.tar.gz
tar -xzvf openssl-1.0.1j.tar.gz
cd openssl-1.0.1j
./config
make depend
sudo make install
sudo ln -sf /usr/local/ssl/bin/openssl `which openssl`
cd ~
openssl version -v

echo "Installing Astro Wallet"
git clone https://github.com/equisde/Astro_Blockchain
cd Astro_Blockchain
git checkout master
git pull

cd src
make OPENSSL_INCLUDE_PATH=/usr/local/ssl/include OPENSSL_LIB_PATH=/usr/local/ssl/lib -f makefile.unix

sudo yes | cp -rf astrod /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Populate astro.conf"
mkdir ~/.astro
echo -e "daemon=1\listen=1\rpcuser=user\rpcpassword=changethispassword\nativetor=0" > ~/.astro/astro.conf


echo "Back to Compiled astrod Binary Folder"
cd ~/Astro_Blockchain/src
                ;;
4) echo 4 "Update astrod 18.04"
echo "Updating Astro Wallet"
cd ~/Astro_Blockchain || exit
git checkout master
git pull

cd src
make OPENSSL_INCLUDE_PATH=/usr/local/ssl/include OPENSSL_LIB_PATH=/usr/local/ssl/lib -f makefile.unix

sudo yes | cp -rf astrod /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Back to Compiled astrod Binary Folder"
cd ~/Astro_Blockchain/src
                ;;
esac
echo Selected $choice
