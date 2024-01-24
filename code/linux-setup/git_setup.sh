# set up github ssh

# add new ssh key
ssh-keygen -t ed25519 -C "zachhoppinen@gmail.com"
eval "$(ssh-agent -s)"

echo "Host github.com" >> ~/.ssh/config
echo "  AddKeysToAgent yes" >> ~/.ssh/config
echo "  IdentityFile ~/.ssh/id_ed25519" >> ~/.ssh/config


# now you need to go to github to add your ssh key
# https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account
echo "Copy and add this key to your github from upper left user icon//settings//SSH and GHG keys//New SSH Key or Add SSH Key"
echo "~/.ssh/id_ed25519.pub is:"
echo "$(<~/.ssh/id_ed25519 )"
# set up username and email

git config --global user.name "Zach Hoppinen"
git config --global user.email "Zachhoppinen@gmail.com"
