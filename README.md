1) Get the certificate from your site (443=HTTPS port)

openssl s_client -connect us-central1-check-release-265504.cloudfunctions.net:443
openssl s_client -connect us-central1-watering-can-271217.cloudfunctions.net:443

2) copy the certificate (from "-----BEGIN CERTIFICATE-----" to "-----END CERTIFICATE-----") and paste into a file (cert.perm).

3) Then use the cert.perm to generate SHA1 fingerprint

openssl x509 -noout -in ./cert.perm -fingerprint -sha1
