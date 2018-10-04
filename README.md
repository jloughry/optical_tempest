This is the C code that appears in Appendix B of [1].

It uses the Caps Lock LED on your keyboard as a covert channel to transmit a
message optically at 50 bit/s. It works with USB keyboards now. The encoding
is the same as RS-232 8N1 (8 bits, no parity, one stop bit) and ought to be
receivable by any UART. When run, the Caps Lock LED will flicker visibly for
about ten seconds.

Ported to Linux 3rd October 2018.

TODO: make it cross-platform to Linux, FreeBSD, Solaris, and macOS.

References:

[1] J. Loughry and D.A. Umphress. 'Information Leakage from Optical Emanations'.
*ACM Trans. Info. Sys. Sec.* **5**(3), pp. 262&ndash;289, 2002.

A copy of Refererence 1 in PDF is in this directory.

