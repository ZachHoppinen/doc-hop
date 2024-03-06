# generate new key if you don't already have one
ssh-keygen -f ~/.ssh/id_rsa

# copy public key to the server
ssh-copy-id -i ~/.ssh/ida_rsa user@host

