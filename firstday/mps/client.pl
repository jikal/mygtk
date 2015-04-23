#!/usr/bin/perl

use IO::Socket;

$c = IO::Socket::INET->new( PeerAddr => 'localhost',
							PeerPort => 8000 )
		or die "cannot connect: $!";
print $c "hello world\n";
print <$c>;
