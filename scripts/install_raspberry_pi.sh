#!/bin/bash
# install.sh

cd ../
sudo apt-get update
sudo apt-get install -y python3-pip
python3 -m pip install virtualenv
python3 -m virtualenv -p python3 env
. env/bin/activate

pip install -r worker/requirements.txt
pip install -r server/requirements.txt
