﻿#include<fast_io.h>
#include<fast_io_device.h>
#include<fast_io_driver/openssl_driver.h>

/*
Need to install OpenSSL first
*/

int main(int argc,char** argv)
{
	using namespace fast_io::mnp;
	if(argc!=2)
	{
		perr("Usage: ",os_c_str(*argv)," <file>\n");
		return 1;
	}
	auto t0{fast_io::posix_clock_gettime(fast_io::posix_clock_id::realtime)};
	fast_io::ossl::sha256_context ctx;
	fast_io::ibuf_file ibf(os_c_str(argv[1]));
	auto transmitted{transmit64(as_file(ctx),ibf)};
	ctx.do_final();
	println(hash_digest(ctx)," *",os_c_str(argv[1]),"\nTransmitted:",transmitted," bytes\tElapsed Time:",fast_io::posix_clock_gettime(fast_io::posix_clock_id::realtime)-t0);
}