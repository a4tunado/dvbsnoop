/*
$Id: datagram.c,v 1.19 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/
 
 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 --  Network IP data
 --  RFC 791    IPv4
 --  RFC 2460   IPv6
 --  RFC 768    UDP

 IP & UDP header code provided by Stéphane Esté-Gracias



$Log: datagram.c,v $

*/




#include "dvbsnoop.h"
#include "misc/hexprint.h"
#include "misc/output.h"




//
// -- IP datagramm bytes decoding...
//

void   net_IP_data (int v, u_char *b, int len)
{

  int ip_version;
  int protocol = -1;


//  print_databytes (v, "IP_datagram_bytes", b, len);

    out_NL (v);
    out_nl (v,"IP_datagram_bytes:");

    indent (+1);

    ip_version = outBit_Sx_NL (v, "Version: ", b, 0, 4);

         if (ip_version == 4) {
		 // -- RFC 791 IPv4

		 int header_len;
		 int ip;

		 header_len = outBit_Sx_NL (v, "IP header length: ", b, 4, 4);
		 outBit_Sx_NL (v, "Type of service: ", b, 8, 8);
		 outBit_Sx_NL (v, "Total length: ", b, 16, 16);
		 outBit_Sx_NL (v, "Identification: ", b, 32, 16);
		 outBit_Sx_NL (v, "Reserved: ", b, 48, 1);
		 outBit_Sx_NL (v, "DF: ", b, 49, 1);
		 outBit_Sx_NL (v, "MF: ", b, 50, 1);
		 outBit_Sx_NL (v, "Fragment offset: ", b, 51, 13);
		 outBit_Sx_NL (v, "Time to live: ", b, 64, 8);
		 protocol = outBit_Sx_NL (v, "Protocol: ", b, 72, 8);
		 outBit_Sx_NL (v, "Header checksum: ", b, 80, 16);

		 ip = getBits (b, 0, 96, 32);
		 out (v,"Source address: %08lx [= ", ip);
		 displ_IPv4_addr (v, ip);
		 out_nl (v,"]");

		 ip = getBits (b, 0, 128, 32);
		 out (v,"Destination address: %08lx [= ", ip);
		 displ_IPv4_addr (v, ip);
		 out_nl (v,"]");

		 b   += (5*4);		// 5*4 = header length
		 len -= (5*4);


		 // -- IPv4 Options & Padding
		 // ---  n = number of options
		 // ---  Total bit length: ( ( 5+n ) * 32 ), 5 is minimum header

		 if (header_len > 5) {
		 	// --  TODO Options & Padding
		 	print_databytes (v, "Options & Padding ", b, len);
		 	b   += (header_len-5)*4;
			len -= (header_len-5)*4;
		 }


	 } else if (ip_version == 6) {
		 // -- RFC 2460 for IPv6
		 struct IPv6ADDR x;
 
		 outBit_Sx_NL (v, "Traffic class: ", b, 4, 8);
		 outBit_Sx_NL (v, "Flow label: ", b, 12, 20);
		 outBit_Sx_NL (v, "Payload length: ", b, 32, 16);
		 protocol = outBit_Sx_NL (v, "Next header: ", b, 48, 16);
		 outBit_Sx_NL (v, "Hop limit: ", b, 64, 16);
 
		 getIPv6Addr (b+8, &x);
		 out (v, "Source address: %08lx%08lx%08lx%08lx [= ",
			 x.ip[0], x.ip[1], x.ip[2], x.ip[3] );
			 displ_IPv6_addr (4, &x);
		 out_nl (v,"]");

		 getIPv6Addr (b+24, &x);
		 out (v, "Destination address: %08lx%08lx%08lx%08lx [= ",
			 x.ip[0], x.ip[1], x.ip[2], x.ip[3] );
			 displ_IPv6_addr (4, &x);
		 out_nl (v,"]");

		 b   += 40;
		 len -= 40;
	 }


	 // -- ICMP,  RFC 792
	 if (protocol == 1) {
		 // -- TODO
	 }

	 // -- TCP,  RFC 793
	 if (protocol == 6) {
		 // -- TODO
	 }

	 // -- UDP datagram,  RFC 768
	 if (protocol == 17) {
		 int udp_header_len;

		 out_NL (v);
		 out_nl (v,"UDP_datagram_bytes: ");

 		 indent (+1);

		 outBit_Sx_NL (v, "Source port: ", b,  0, 16);
		 outBit_Sx_NL (v, "Destination port: ",	b, 16, 16);
		 udp_header_len = outBit_Sx_NL (v, "Length: ", b, 32, 16);
		 outBit_Sx_NL (v, "Checksum: ",	b, 48, 16);

		 print_databytes (v, "Data", b+8, udp_header_len-8);

		 b   += udp_header_len;	// -- length is complete header + data
		 len -= udp_header_len;

		 indent (-1);
	 }



	 if (len > 0) {
	 	 print_databytes (v, "Unknown Data (todo...)", b, len);
		 b   += len;
		 len -= len;
	 }

	 out_NL (v);
	 indent (-1);

}




