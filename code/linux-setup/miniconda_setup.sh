##https://javedhassans.medium.com/install-miniconda-on-linux-from-the-command-line-in-5-steps-403912b3f378

# create a directory to install minicaonda in
mkdir -p ~/miniconda3

# download latest miniconda version
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh

# run the install script
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3

# delete the intall script
rm -rf ~/miniconda3/miniconda.sh

# add a conda initialize to your bash
~/miniconda3/bin/conda init bash

# You will need to restart or source your startup bashrc or bash_profile at this point.
# Verify the installaton 
conda list


