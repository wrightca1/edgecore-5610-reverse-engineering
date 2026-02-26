# Manual SSH key install on the switch

If `ssh-copy-id` fails, add your key by hand.

## 1. SSH into the switch with your password

```bash
ssh <SWITCH_USER>@<LIVE_SWITCH_IP>
```

## 2. On the switch, add your public key

Run these on the switch (replace the key line with your own from `cat ~/.ssh/id_ed25519.pub` on your Mac):

```bash
mkdir -p ~/.ssh
chmod 700 ~/.ssh
echo "PASTE_YOUR_PUBLIC_KEY_LINE_HERE" >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
```

## 3. Get your public key line

On your Mac:

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the whole line (starts with ssh-ed25519 or ssh-rsa) and use it in place of `PASTE_YOUR_PUBLIC_KEY_LINE_HERE` above.

## 4. Test

From your Mac: `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>` — should log in without a password.
