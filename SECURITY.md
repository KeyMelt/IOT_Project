# Security policy

## Supported versions

Security fixes are applied on the `main` branch. Tagged releases are not used for this educational IoT project; use the latest `main` commit for deployments.

## Reporting a vulnerability

Please **do not** open a public GitHub issue for security-sensitive reports.

1. Use [GitHub Security Advisories](https://github.com/KeyMelt/IOT_Project/security/advisories/new) for this repository, or contact the maintainers privately.
2. Include steps to reproduce, impact, and any suggested fix if you have one.

We will acknowledge reports within a reasonable time and work on a fix before public disclosure when possible.

## Secrets and credentials

- Never commit `TrackerCode/secrets.h` or real Blynk auth tokens.
- Rotate any token that was accidentally committed or shared.
- Use `secrets.h.example` and `.env.example` as templates only.
