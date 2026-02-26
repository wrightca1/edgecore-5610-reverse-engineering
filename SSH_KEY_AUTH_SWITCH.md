# Why key auth fails to the Cumulus switch (<LIVE_SWITCH_IP>)

## Two causes (both fixed)

### 1. Ed25519 not supported

The switch runs **OpenSSH 6.0p1**. **Ed25519** was added in OpenSSH **6.5**. Your default key is Ed25519; the server does not support it and silently rejects it.

### 2. RSA signature algorithm

OpenSSH 8.8+ clients disable the legacy **ssh-rsa** (SHA1) signature. The switch only supports that. So even with an RSA key you get “no mutual signature algorithm” unless the client re-enables it.

## Fix (done via sshpass)

1. **RSA key** was created and copied: `~/.ssh/id_rsa_switch` (script: `scripts/reverse-engineering/copy-rsa-key-to-switch.sh`).
2. **Use legacy algorithm** when connecting. Add to `~/.ssh/config`:

```
Host <LIVE_SWITCH_IP>
  User cumulus
  IdentityFile ~/.ssh/id_rsa_switch
  PubkeyAcceptedAlgorithms +ssh-rsa
```

Then `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>` uses key auth with no password.

One-liner without config:

```bash
ssh -i ~/.ssh/id_rsa_switch -o PubkeyAcceptedAlgorithms=+ssh-rsa <SWITCH_USER>@<LIVE_SWITCH_IP>
```

## Verified

- With `PubkeyAcceptedAlgorithms=+ssh-rsa` and `id_rsa_switch`, key auth works (no sshpass).
- authorized_keys on switch contains the RSA public key.
