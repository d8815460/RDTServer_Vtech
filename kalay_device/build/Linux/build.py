#!/usr/bin/python

import sys
import os
import threading

crossinfo = [
['x86', "", '-m32 -x c -s -Wvla -std=c99 -pedantic -Wall -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC'],
['x86_centOS', "", '-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -m32 -x c -s -Wvla -std=c99 -pedantic -Wall -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC'],
['x64', "", ' -x c -s -Wvla -std=c99 -O2 -pedantic -Wall -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC'],
['x64_centOS', "", '-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -x c -g -Wvla -std=c99 -O2 -pedantic -Wall -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC'],
['Arm9_GM8120_3.4.1', '/opt/cross-project/arm/grainmedia/Arm9_GM8120_3.4.1/3.4.1/bin/arm-linux-', '-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_GM8120_3.4.6', '/opt/cross-project/arm/grainmedia/Arm9_GM8120_3.4.6/3.4.6/bin/arm-linux-', '-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_GM8126_4.4.0', '/opt/cross-project/arm/grainmedia/Arm9_GM8126_4.4.0/ARMv5TE_4.4.0/bin/arm-none-linux-gnueabi-', '-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_GM8161_3.4.6', '/opt/cross-project/arm/grainmedia/Arm9_GM8161_3.4.6/uc_3.4.6/bin/arm-linux-uclibc-', '-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_DM365_4.2.0', '/opt/cross-project/arm/texasinstruments/Arm9_DM365_4.2.0/mon_4.2.0/pro/devkit/arm/v5t_le/bin/arm_v5t_le-', '-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RalinkRT5350_3.4.2', '/opt/cross-project/mips/mtk/Mips_RalinkRT5350_3.4.2/ralink_3.4.2/bin/mipsel-linux-uclibc-','-x c -s -std=c99 -O2 -Wall -DNOSETCLOCK -D_GNU_SOURCE -DIOTC_NOIFADDRS'],
['Mips_MST6i78_4.3.2', '/opt/cross-project/mips/mtk/Mips_MST6i78_4.3.2/4.3.2/bin/mips-linux-gnu-', '-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_MST6i98_4.3.2', '/opt/cross-project/mips/mtk/Mips_MST6i98_4.3.2/4.3.2/bin/mips-linux-gnu-', '-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_AR9331_4.3.3', '/opt/cross-project/mips/qualcomm/Mips_AR9331_4.3.3/atheros/build/gcc-4.3.3/build_mips/staging_dir/usr/bin/mips-linux-','-x c -s -O2 -Wall -std=c99 -D_GNU_SOURCE -DNOSETCLOCK -DIOTC_BIG_ENDIAN  -DIOTC_NOIFADDRS'],
['Arm11_SSD1935_3.4.6', '/opt/cross-project/arm/solomon/Arm11_SSD1935_3.4.6/SSD_3.4.6/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_GM8126_4.4.7','/opt/cross-project/arm/grainmedia/Arm9_GM8126_4.4.7/8126_4.4.7/bin/arm-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RalinkRTF5350_3.4.2', '/opt/cross-project/mips/mtk/Mips_RalinkRTF5350_3.4.2/buildroot-gcc342/bin/mipsel-linux-','-x c -s -std=c99 -O2 -Wall -DNOSETCLOCK -D_GNU_SOURCE -DIOTC_NOIFADDRS'],
['Arm11_CLFSX_4.4.1', '/opt/cross-project/arm/X/Arm11_CLFSX_4.4.1/clfs-sbt/cross-tools/bin/arm-sbtred-linux-gnueabi-','-x c -s -march=armv6 -mtune=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp -Wall -O2 -std=gnu99 -DNO_MUTEX_RECURSIVE --sysroot=/space/clfs-sbt/'],
['Arm9_Q1X_4.2.3', '/opt/cross-project/arm/X/Arm9_Q1X_4.2.3/arm-2008q1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_FSL_4.4.4', '/opt/cross-project/arm/freescale/Arm_FSL_4.4.4/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_DM365_3.4.3', '/opt/cross-project/arm/texasinstruments/Arm9_DM365_3.4.3/v5t_le-mv401_uc/bin/arm_v5t_le-','-x c -s -std=gnu99 -O0 -Wall -DNOSETCLOCK -D_GNU_SOURCE -DIOTC_NOIFADDRS'],
['Arm9_Hi3512_4.4.1', '/opt/cross-project/arm/hisilicon/Arm9_Hi3512_4.4.1/hisi-linux/x86-arm/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3515_3.4.3', '/opt/cross-project/arm/hisilicon/Arm9_Hi3515_3.4.3/Hi3515_gcc-3.4.3-uClibc-0.9.28/x86-arm/gcc-3.4.3-uClibc-0.9.28/bin/arm-hisi-linux-','-x c -s -std=c99 -O2 -Wall -DNOSETCLOCK -D_GNU_SOURCE -DIOTC_NOIFADDRS'],
['Mips_Realtek8196C_3.4.6', '/opt/cross-project/mips/realtek/Mips_Realtek8196C_3.4.6/rsdk-1.3.6/bin/mips-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN -DIOTC_NOIFADDRS'],
['Mips_Realtek8196D_4.4.5', '/opt/cross-project/mips/realtek/Mips_Realtek8196D_4.4.5/rsdk-1.5.5/bin/mips-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN -DIOTC_NOIFADDRS'],
['Arm9_N32905U1DN_4.2.1', '/opt/cross-project/arm/nutoton/Arm9_N32905U1DN_4.2.1/arm_linux_4.2/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_Realtek8197D_4.4.5', '/opt/cross-project/mips/realtek/Mips_Realtek8197D_4.4.5/rsdk-1.5.5-5281-EB/bin/mips-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN -DIOTC_NOIFADDRS'],
['Mips_RalinkRT3352_3.4.2', '/opt/cross-project/mips/mtk/Mips_RalinkRT3352_3.4.2/buildroot-gcc342/bin/mipsel-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_Hi3518_4.4.1', '/opt/cross-project/arm/hisilicon/Arm9_Hi3518_4.4.1/arm-hisiv100nptl-linux/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3518_4.4.1_CLOCK_MONOTONIC', '/opt/cross-project/arm/hisilicon/Arm9_Hi3518_4.4.1/arm-hisiv100nptl-linux/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DUSE_CLOCK_MONOTONIC'],
['Arm9_GM8181_3.4.3', '/opt/cross-project/arm/grainmedia/Arm9_GM8181_3.4.3/8181_3.4.3/gcc-3.4.4-glibc-2.3.5/arm-linux/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_Realtek8196E_3.4.6', '/opt/cross-project/mips/realtek/Mips_Realtek8196E_3.4.6/rtl819x-SDK-v3.4.6_toolchain/rsdk-1.5.5-4181-EB-2.6.30-0.9.30.3-110225/bin/mips-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN -DIOTC_NOIFADDRS -DIOTC_LOW_BUF_SIZE'],
['Arm9_Hi3520A_4.4.1', '/opt/cross-project/arm/hisilicon/Arm9_Hi3520A_4.4.1/hisi-linux/x86-arm/arm-hisiv100-linux/target/bin/arm-hisiv100-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm11_SSD1937_4.3.2', '/opt/cross-project/arm/solomon/Arm11_SSD1937_4.3.2/arm/4.3.2/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Armv5TE_FH8755_4.4.0', '/opt/cross-project/arm/fullhan/Armv5TE_FH8755_4.4.0/arm-none-linux-gnueabi-4.4.0/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Ti8107_4.3.3', '/opt/cross-project/arm/texasinstruments/Arm9_Ti8107_4.3.3/arm-2009q1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3516_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3516_4.4.1/Hi3516_4.4.1/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Unicore_SEP6200_4.4.2','/opt/cross-project/unicore/Unicore_SEP6200_4.4.2/gnu-toolchain-unicore/uc4-1.0-beta-hard-RHELAS5/bin/unicore32-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
#['Arm926EJS_X_4.2.1','/opt/cross-project/arm/X/Arm926EJS_X_4.2.1/arm_linux_4.2_Arm9_26EJSid/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_A5S55_4.6.1','/opt/cross-project/arm/ambarella/Arm9_A5S55_4.6.1/arm-2011.09/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Armv7a_Hi8107_4.4.6','/opt/cross-project/arm/hisilicon/Armv7a_Hi8107_4.4.6/hik_toolchain/arm-hik_v7a-linux-uclibcgnueabi/bin/arm-hik_v7a-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_GM8161_3.4.4','/opt/cross-project/arm/grainmedia/Arm9_GM8161_3.4.4/8181_3.4.3/gcc-3.4.4-glibc-2.3.5/arm-linux/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3515A_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3515A_4.4.1/arm-hisiv100nptl-linux/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3531Libc_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3531Libc_4.4.1/arm-hisi3716C_V200-linux-libc/bin/arm-hisiv200-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_MT7620A_3.4.2','/opt/cross-project/mips/mtk/Mips_MT7620A_3.4.2/buildroot-gcc342/bin/mipsel-linux-uclibc-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_trident_4.5.2','/opt/cross-project/arm/trident/gcc-4.5.2_glibc/bin/arm-cortex-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_BCM7424B2_4.5.3','/opt/cross-project/mips/broadcom/Mips_BCM7424B2_4.5.3/stbgcc-4.5.3-2.4/bin/mipsel-linux-uclibc-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Ti365_4.2.0','/opt/cross-project/arm/texasinstruments/Arm9_Ti365_4.2.0/TI365/devkit/arm/v5t_le/bin/arm_v5t_le-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3716C_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3716C_4.4.1/arm-hisi3716C_V200-linux/arm-hisiv200-linux/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_N32905U1DN_4.4.1','/opt/cross-project/arm/nutoton/Arm9_N32905U1DN_4.4.1/arm-2009q3/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_AR9331_4.6.3','/opt/cross-project/mips/qualcomm/Mips_AR9331_4.6.3/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Arm9_EPN7530X_4.5.2','/opt/cross-project/arm/X/Arm9_EPN7530X_4.5.2/bin/arm-cortex-linux-gnueabi-','-x c -fPIC -std=c99 -O0 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Arm11_A5S66_4.6.1','/opt/cross-project/arm/ambarella/Arm11_A5S66_4.6.1/arm-2011.09/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm11_IMAPx210_4.5.4','export LD_LIBRARY_PATH=/opt/cross-project/arm/infotmic/Arm11_IMAPx210_4.5.4/lib/; /opt/cross-project/arm/infotmic/Arm11_IMAPx210_4.5.4/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_jiakeX_4.4.1','export LD_LIBRARY_PATH=''; /opt/cross-project/arm/X/Arm9_jiakeX_4.4.1/arm-2009q3/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_AML8723M3_4.6','/opt/cross-project/arm/amlogic/Arm9_AML8723M3_4.6/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_AK3918_4.4.1','/opt/cross-project/arm/anyka/Arm9_AK3918_4.4.1/arm-2009q3/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_IMAPx15_4.7.3','/opt/cross-project/arm/infotmic/Arm_IMAPx15_4.7.3/Linaro/linaro-arm-linux-gnueabihf-4.7/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_AT91SAM9G45_4.5.1','/opt/cross-project/arm/atmel/Arm9_AT91SAM9G45_4.5.1/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_S3C2440_4.1.2','/opt/cross-project/arm/samsung/Arm9_S3C2440_4.1.2/bin/arm-angstrom-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Armv7a_C2200_4.5.4','export PATH=/opt/cross-project/arm/mindspeed/Armv7a_C2200_4.5.4/toolchain-arm_v7-a_gcc-4.5-linaro_glibc-2.14.1_eabi/bin:${PATH}:/usr/sbin:/sbin; export STAGING_DIR=/opt/cross-project/arm/mindspeed/Armv7a_C2200_4.5.4; /opt/cross-project/arm/mindspeed/Armv7a_C2200_4.5.4/toolchain-arm_v7-a_gcc-4.5-linaro_glibc-2.14.1_eabi/bin/arm-openwrt-linux-gnueabi-','-x c -I/usr/local/victor_mnt/john_wang/toolchain-arm_v7-a_gcc-4.5-linaro_glibc-2.14.1_eabi/include/ -L/usr/local/victor_mnt/john_wang/toolchain-arm_v7-a_gcc-4.5-linaro_glibc-2.14.1_eabi/lib -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_N32903_4.2.1','/opt/cross-project/arm/nutoton/Arm9_N32903_4.2.1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Armv7_TCC8925_4.4.1','/opt/cross-project/arm/telechips/Armv7_TCC8925_4.4.1/codesourcery/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm7_Ti8168_4.3.3','/opt/cross-project/arm/texasinstruments/Arm7_Ti8168_4.3.3/arm-2009q1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3520D_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3520D_4.4.1/arm-hisi3716C_V200-linux/arm-hisiv200-linux/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3521_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3521_4.4.1/arm-hisi3716C_V200-linux/arm-hisiv200-linux/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3531_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3531_4.4.1/arm-hisiv100nptl-linux/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3535_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3535_4.4.1/arm-hisi3716C_V200-linux/arm-hisiv200-linux/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_380_4.6.3','/opt/cross-project/arm/X/Arm9_380_4.6.3/4.6.3/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['x86_TS269HX_4.5.1','/opt/cross-project/x86-intelCE/x86_TS269HX_4.5.1/build_i686/staging_dir/bin/i686-cm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Armv5TE_GM8139_4.4.0','/opt/cross-project/arm/grainmedia/Armv5TE_GM8139_4.4.0/bin/arm-unknown-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm11_BCM2835_4.8.3','/opt/cross-project/arm/broadcom/ARM_BCM2835_4.8.3/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm11_BCM2835_4.5.1','/opt/cross-project/arm/broadcom/Arm11_BCM2835_4.5.1/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_ASC8850_4.3.5','/opt/cross-project/arm/nxp/Arm_ASC8850_4.3.5/Mozart_toolchain/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/nxp/Arm_ASC8850_4.3.5/Mozart_toolchain/arm-eabi-uclibc'],
['Arm_X41_4.8.2','/opt/cross-project/arm/linaro/Arm_X41_4.8.2/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['x86_X1000_4.7.2','export PATH=/home/build/arduino-1.5.3/hardware/tools/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux-uclibc/:$PATH; i586-poky-linux-uclibc-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/home/build/arduino-1.5.3/hardware/tools/sysroots/i586-poky-linux-uclibc'],
['Arm_2518C_4.4.1','/opt/cross-project/arm/hisilicon/Arm_2518C_4.4.1/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_AIT8455P_4.4.1','export LD_LIBRARY_PATH=/opt/cross-project/arm/ait/Arm_AIT8455P_4.7.3/lib; /opt/cross-project/arm/ait/Arm_AIT8455P_4.7.3/bin/arm-buildroot-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_Mozart385s_4.3.5','/opt/cross-project/arm/amlogic/Arm_Mozart385s_4.3.5/usr/bin/arm-unknown-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -I/opt/cross-project/arm/amlogic/Arm_Mozart385s_4.3.5/usr/bin/include -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/amlogic/Arm_Mozart385s_4.3.5'],
['Arm_BCM4709_4.8.3','/opt/cross-project/arm/broadcom/Arm_BCM4709_4.8.3/toolchain-arm_cortex-a9_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_GM8287_4.4.0','/opt/cross-project/arm/grainmedia/Arm_GM8287_4.4.0/bin/arm-unknown-linux-uclibcgnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_ASC8848A_4.3.5','/opt/cross-project/arm/nxp/Arm_ASC8848A_4.3.5/arm-2010q1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_5802_4.4.1','/opt/cross-project/arm/amlogic/Arm_5802_4.4.1/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64  --sysroot=/opt/cross-project/arm/amlogic/Arm_5802_4.4.1/arm-eabi-uclibc/'],
['Mips_M200_4.7.2','/opt/cross-project/mips/Ingenic/Mips_M200_4.7.2/mips-gcc472-glibc216-32bit-mxu-el/bin/mips-linux-gnu-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_GM8138S_4.4.0','/opt/cross-project/arm/grainmedia/Arm_GM8138S_4.4.0/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mipsel_SPCA6350_4.6.4','/opt/cross-project/mips/iCatchTek/Mipsel_SPCA6350_4.6.4/usr/bin/mipsel-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_2010ql_4.4.1','/opt/cross-project/arm/X/Arm_2010ql_4.4.1/arm-2010q1/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_2011.09_4.6.1','/opt/cross-project/arm/X/Arm_2011.09_4.6.1/arm-2011.09/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_Am3358_4.7.3','/opt/cross-project/arm/texasinstruments/Arm_Am3358_4.7.3/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_AM3358_4.9.2','/opt/cross-project/arm/X/Arm_AM3358_4.9.2/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_Realtek1195_4.6','arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_SQ6610A_4.3.5','/opt/cross-project/arm/sq/Arm_SQ6610A_4.3.5/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/sq/Arm_SQ6610A_4.3.5/arm-eabi-uclibc'],
['Mips_JN5168_4.6', '/opt/cross-project/mips/nxp/Mips_JN5168_4.6/bin/mips-openwrt-linux-uclibc-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN -DIOTC_NOIFADDRS'],
['Arm9_330s_4.3.5','/opt/cross-project/arm/vatics/Arm9_330s_4.3.5/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 --sysroot=/opt/cross-project/arm/vatics/Arm9_330s_4.3.5/arm-eabi-uclibc'],
['Arm_S2L_4.9.1-i686','/opt/cross-project/arm/ambarella/Arm_S2L_4.9.1-i686/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_JZ4775_4.1.2','/opt/cross-project/mips/Ingenic/Mips_JZ4775_4.1.2/mipseltools-gcc412-glibc261-4775/bin/mipsel-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_PhilipsA20_4.8.2','/opt/cross-project/arm/allwinner/Arm_PhilipsA20_4.8.2/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -mfloat-abi=hard -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_AK3918_4.4.1','/opt/cross-project/arm/anyka/Arm9_AK3918_4.4.1_qineng/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_NXP8848A','/opt/cross-project/arm/nxp/Arm_NXP8848A/Mozart_Toolchain/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/nxp/Arm_NXP8848A/Mozart_Toolchain/arm-eabi-uclibc'],
['Arm_N32926_4.2','/opt/cross-project/arm/nuvoton/Arm_N32926_4.2/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_SN98601_4.5.2','/opt/cross-project/arm/X/Arm_SN98601_4.5.2/crosstool-4.5.2/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm926EJS_N3292x_4.2','/opt/cross-project/arm/nuvoton/Arm926EJS_N3292x_4.2/bin/arm-linux-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Armv11_X210_4.3.3','/opt/cross-project/arm/infotmic/Armv11_X210_4.3.3/toolchain_infotm_1.2.2/bin/arm-infotm-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Mips_Artpec4_4.7.2','/usr/local/mipsisa32r2el/r23/bin/mipsisa32r2el-axis-linux-gnu-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Mips_MT7620_4.6.3','/opt/cross-project/mips/mtk/Mips_MT7620_4.6.3/buildroot-gcc463/usr/bin/mipsel-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_S2L_4.8.2','/opt/cross-project/arm/ambarella/Arm_S2L_4.8.2/linaro-multilib-2013.09-gcc4.8/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm11_FH8810_4.3.2','/opt/cross-project/arm/fullhan/Arm11_FH8810_4.3.2/arm-fullhan-linux-uclibcgnueabi/bin/arm-fullhan-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
#['Mips_X_4.6.3','/opt/cross-project/mips/X/Mips_X_4.6.3/buildroot-gcc463/usr/bin/mipsel-buildroot-linux-uclibc-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS '],
['Mips_NT96660_4.8.1','/opt/cross-project/mips/novatek/Mips_NT96660_4.8.1/mipsel-24kec-linux-glibc/bin/mipsel-24kec-linux-gnu-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Arm_A7L_4.7.3','/opt/cross-project/arm/ambarella/Arm_A7L_4.7.3/arm-2013.05/bin/arm-none-linux-gnueabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
['Armv5TE_X2_4.4.0','/opt/cross-project/arm/X/Armv5TE_X2_4.4.0/toolchain_gnueabi-4.4.0_ARMv5TE/usr/bin/arm-unknown-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
#['Arm_HiXXX_3.4.3','/opt/cross-project/arm/hisilicon/Arm_HiXXX_3.4.3/hi-arm-linux/gcc-3.4.3-uClibc-0.9.28/usr/bin/arm-hismall-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_GM8139s_4.4.0','/opt/cross-project/arm/grainmedia/Arm_GM8139s_4.4.0/arm-none-linux-gnueabi-4.4.0_linux-3.3/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['ArmCortexA8_AM3352_4.9.2','/opt/cross-project/arm/telechips/ArmCortexA8_AM3352_4.9.2/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_RT5350_4.8.3','/opt/cross-project/mips/ralink/Mips_RT5350_4.8.3/OpenWrt-Toolchain-ramips-rt305x_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-i686/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm9_NXP8181_4.1.2','/opt/cross-project/arm/nxp/Arm9_NXP8181_4.1.2/emlix/pnx8181/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm926EJ-S_SPG101_4.4.0','/opt/cross-project/arm/keyasic/Arm926EJ-S_SPG101_4.4.0/arm-uclibc/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/keyasic/Arm926EJ-S_SPG101_4.4.0/arm-uclibc'],
['Arm_S2LM_4.9.2','/opt/cross-project/arm/ambarella/Arm_S2LM_4.9.2/arm-amba-linux-uclibcgnueabihf-2014.11-gcc4.9/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_BCM97584_4.5.4','/opt/cross-project/mips/broadcom/Mips_BCM97584_4.5.4/stbgcc-4.5.4-2.6/bin/mipsel-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Armv7A9_Exynos4412_4.1.2','/opt/cross-project/arm/samsung/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA9_S2L55M_4.8.2','/opt/cross-project/arm/ambarella/ArmCortexA9_S2L55M_4.8.2/linaro-multilib-2013.09-gcc4.8/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_88AP168_4.4.5','/opt/cross-project/arm/marvell/Arm_88AP168_4.4.5/arm-marvell-linux-gnueabi-vfp/bin/arm-marvell-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_M200_v2_4.7.2','/opt/cross-project/mips/Ingenic/Mips_M200_v2_4.7.2/mips-gcc472-glibc216-64bit/bin/mips-linux-gnu-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm926EJ-S_LPC3240_4.6.3','/opt/cross-project/arm/nxp/Arm926EJ-S_LPC3240_4.6.3/toolchain-arm_gcc-4.6-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_RTL8881_4.8.3','/opt/cross-project/mips/realtek/Mips_RTL8881_4.8.3/rsdk-4.8.3-5281-EL-3.10-u0.9.33-m32ut-141222/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_RTL8881_4.4.5','/opt/cross-project/mips/realtek/Mips_RTL8881_4.4.5/rsdk-1.5.5-5281-EB-2.6.30-0.9.30.3-110714/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS -DIOTC_BIG_ENDIAN'],
['Arm_SN98600_4.5.2','/opt/cross-project/arm/X/Arm_SN98600_4.5.2/crosstool-4.5.2/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_Hi3516D_4.8.3','/opt/cross-project/arm/hisilicon/Arm_Hi3516D_4.8.3/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_Hi3516A_4.8.3','/opt/cross-project/arm/hisilicon/Arm_Hi3516A_4.8.3/arm-hisiv400-linux/bin/arm-hisiv400-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['ARMv5TE_NVS3660A_4.4.0','/opt/cross-project/arm/nextchip/ARMv5TE_NVS3660A_4.4.0/arm-none-linux-gnueabi-4.4.0_ARMv5TE/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_S2L_4.9.1','/opt/cross-project/arm/ambarella/Arm_S2L_4.9.1/linaro-multilib-2014.06-gcc4.9/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_AT91SAM9G45_4.0.0','/opt/cross-project/arm/atmel/Arm_AT91SAM9G45_4.0.0/compiler/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_BCM2836_4.8.3','/opt/cross-project/arm/broadcom/Arm_BCM2836_4.8.3/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_MT7688_4.6.3','/opt/cross-project/mips/mtk/Mips_MT7688_4.6.3/buildroot-gcc342/bin/mipsel-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_4KC_4.0.0','/opt/cross-project/mips/broadcom/Mips_4KC_4.0.0/mips-broadcom/bcm53314/eldk/usr/bin/mips_4KC-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS -DIOTC_BIG_ENDIAN'],
['Arm_BRCM63138_4.6.2','/opt/cross-project/arm/broadcom/Arm_BRCM63138_4.6.2/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_A5S88_4.6.1','/opt/cross-project/arm/ambarella/Arm_A5S88_4.6.1/arm-2011.09/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],	
['Mips_MT7620AOpenwrt_4.8.3','/opt/cross-project/mips/mtk/Mips_MT7620AOpenwrt_4.8.3/OpenWrt-Toolchain-ramips-for-mipsel_24kec+dsp-gcc-4.8-linaro_uClibc-0.9.33.2/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_Hi3521_4.4.6','/opt/cross-project/arm/hisilicon/Arm_Hi3521_4.4.6/work/buildroot_hilinux/output/host/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Arm_A12_4.8.3','/opt/cross-project/arm/ambarella/Arm_A12_4.8.3/arm-2014.05/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],
['Mips_AR9331OpenWrt_4.8.3','/opt/cross-project/mips/qualcomm/Mips_AR9331OpenWrt_4.8.3/OpenWrt-Toolchain-ar71xx-for-mips_34kc-gcc-4.8-linaro_uClibc-0.9.33.2/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_NXP8848A_4.3.5','/opt/cross-project/arm/nxp/Arm_NXP8848A_4.3.5/Mozart_Toolchain/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 --sysroot=/opt/cross-project/arm/nxp/Arm_NXP8848A_4.3.5/Mozart_Toolchain/arm-eabi-uclibc'],
['Mips_MT7620NOpenWrt_4.8.3','/opt/cross-project/mips/mtk/Mips_MT7620NOpenWrt_4.8.3/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_CNC1800L_4.5.1','/opt/cross-project/arm/cavium/Arm_CNC1800L_4.5.1/arm-2010.09-50/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA9_iMX6_4.6.2','/opt/cross-project/arm/freescale/ArmCortexA9_iMX6_4.6.2/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/tq-linaro-toolchain/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm1176_HISI300_4.8.3','/opt/cross-project/arm/hisilicon/Arm1176_HISI300_4.8.3/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_linuxgnu_4.6.1','arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA17_Hi3536_4.8.3','/opt/cross-project/arm/hisilicon/ArmCortexA17_Hi3536_4.8.3/hisi-linux/x86-arm/arm-hisiv400-linux/bin/arm-hisiv400-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_arm-linux-guneabi_4.7.3','arm-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_MT7620A_4.7.3','/opt/cross-project/mips/mtk/Mips_MT7620A_4.7.3/buildroot-gcc-4.7.3-mips32r2-linux-2.6.36/usr/bin/mipsel-linux-uclibc-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA17_Hi3536_4.8.3','/opt/cross-project/arm/hisilicon/ArmCortexA17_Hi3536_4.8.3/hisi-linux/x86-arm/arm-hisiv400-linux/bin/arm-hisiv400-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_MT7620_4.6.4_2','/opt/cross-project/mips/mtk/Mips_MT7620_4.6.4_2/buildroot-eglibc-gcc464/usr/bin/mipsel-buildroot-linux-gnu-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RTL8196E_4.4.5','/opt/cross-project/mips/realtek/Mips_RTL8196E_4.4.5/toolchain/rsdk-1.5.5-4181-EB-2.6.30-0.9.30.3-110225/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Arm9_GM8136_4.4.0','/opt/cross-project/arm/grainmedia/Arm9_GM8136_4.4.0/toolchain_gnueabi-4.4.0_ARMv5TE/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA7_Vinus9_4.4.1','/opt/cross-project/arm/panasonic/ArmCortexA7_Vinus9_4.4.1/arm-2010q1/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_GM8139glib_4.4.0','/opt/cross-project/arm/grainmedia/Arm_GM8139glib_4.4.0/arm-none-linux-gnueabi-4.4.0_linux-3.3/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_AR9331_4.8.3','/opt/cross-project/mips/qualcomm/Mips_AR9331_4.8.3/OpenWrt-Toolchain-ar71xx-for-mips_34kc-gcc-4.8-linaro_uClibc-0.9.33.2/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Arm9_8135s_4.4.0','/opt/cross-project/arm/grainmedia/Arm9_8135s_4.4.0/toolchain_gnueabi-4.4.0_ARMv5TE/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_BIG_ENDIAN'],
['Arm926EJ-S_SN98660_4.5.2','/opt/cross-project/arm/sonix/Arm926EJ-S_SN98660_4.5.2/crosstool-4.5.2/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3520D_4.4.1_glibc','/opt/cross-project/arm/hisilicon/Arm9_Hi3520D_4.4.1_glibc/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_NT96660_4.8.1_uclibc','/opt/cross-project/mips/novatek/Mips_NT96660_4.8.1_uclibc/mipsel-24kec-linux-uclibc/bin/mipsel-24kec-linux-uclibc-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ARM926EJ-S_N32926_4.6.4','/opt/dspg/v1.3.1-rc3/sysroots/x86_64-dspg-linux/usr/bin/armv5te-dspg-linux-gnueabi/arm-dspg-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_M150_4.7.2','/opt/cross-project/mips/Ingenic/Mips_M150_4.7.2/mips-gcc472-glibc216/bin/mips-linux-gnu-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3518EV200_4.4.1','/opt/cross-project/arm/hisilicon/Arm9_Hi3518EV200_4.4.1/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3520D_4.4.1_glibc','/opt/cross-project/arm/Arm9_Hi3520D_4.4.1_glibc/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3535_4.4.1_HIK','/opt/cross-project/arm/hisilicon/Arm9_Hi3535_4.4.1_2/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA7_Hi3516Av300_4.8.3','/opt/cross-project/arm/hisilicon/ArmCortexA7_Hi3516Av300_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_M3881C_4.9.2','/opt/cross-project/arm/vatics/Arm9_M3881C_4.9.2/arm-eabi-uclibc/usr/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_PL1219_4.4.5','/opt/cross-project/arm/prolific/Arm_PL1219_4.4.5/uc_arm-eabi/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_IM1203_3.4.6','/opt/cross-project/arm/jmicron/Arm_IM1203_3.4.6/crosstool/scratchbox/compilers/arm-gcc3.4-uclibc0.9.28/bin/arm-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RST3901_4.8.3','/opt/cross-project/mips/realtek/Mips_RST3901_4.8.3/rsdk-4.8.3-5281-EL-3.10-u0.9.33-m32ut-141222/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_A12_4.9.3','export PATH=/opt/cross-project/arm/hisilicon/Arm_Hi3521A_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/bin; /opt/cross-project/arm/hisilicon/Arm_Hi3521A_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_Hi3521A_4.8.3','/opt/cross-project/arm/hisilicon/Arm_Hi3521A_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['arm-hisiv100-linux-dd','/opt/cross-project/arm/hisilicon/arm-hisiv100-linux-dd/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_Hi3521A_4.8.3_Flag','/opt/cross-project/arm/hisilicon/Arm_Hi3521A_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations'],
['ArmCortexA9_Hi3531A_4.8.3','/opt/cross-project/arm/hisilicon/ArmCortexA9_Hi3531A_4.8.3/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=neon -mno-unaligned-access -fno-aggressive-loop-optimizations'],
['Arm1176JZF-S_CXD4135_4.4.1','/opt/cross-project/arm/sony/Arm1176JZF-S_CXD4135_4.4.1/gnu/gnu-tools/xarina-20120823/x86-linux2/bin/arm-wrs-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 --sysroot=/opt/cross-project/arm/sony/Arm1176JZF-S_CXD4135_4.4.1/gnu/sysroot/xarina-20120906/sysroot'],
['Arm176JZ_CXD4145_4.8.1','/opt/cross-project/arm/sony/Arm176JZ_CXD4145_4.8.1/gnu/sysroots/x86_64-wrlinuxsdk-linux/usr/bin/armv6-vfp-wrs-linux-gnueabi/arm-wrs-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 --sysroot=/opt/cross-project/arm/sony/Arm176JZ_CXD4145_4.8.1/gnu/sysroots/armv6-vfp-wrs-linux-gnueabi'],
['Arm9_Hi3516_4.4.1_2','/opt/cross-project/arm/hisilicon/Arm9_Hi3516_4.4.1_2/arm-hisiv100-linux/bin/arm-hisiv100-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_I1_4.8.3','/opt/cross-project/arm/ait/Arm_I1_4.8.3/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64  -march=armv7-a -mfpu=neon'],
['Mips_MT7688_4.8.3','/opt/cross-project/mips/mtk/Mips_MT7688_4.8.3/OpenWrt-Toolchain-ramips-mt7688_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-uclibc-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_S605-8-32_4.2.1','/opt/cross-project/arm/ACSiP/Arm9_S605-8-32_4.2.1/s605-BSP/ARM-toolchain/arm_linux_4.2/bin/arm-none-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm8_TI816x_4.5.4','/opt/cross-project/arm/ti/Arm8_TI816x_4.5.4/usr/bin/arm-buildroot-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_Hi3516cv200_4.8.3','/opt/cross-project/arm/hisilicon/Arm_Hi3516cv200_4.8.3/osdrv/opensource/toolchain/arm-hisiv400-linux/arm-hisiv400-linux/bin/arm-hisiv400-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA7_Hi3516A_4.8.3','/opt/cross-project/arm/hisilicon/ArmCortexA7_Hi3516A_4.8.3/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA8_AM3554_4.5.3','/opt/cross-project/arm/ti/ArmCortexA8_AM3554_4.5.3/linux-devkit/bin/arm-arago-linux-gnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
#['Arm9_Hi3518E_4.8.3','/opt/cross-project/arm/hisilicon/Arm9_Hi3518E_4.8.3/arm-hisiv300-linux/arm-hisiv300-linux/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RTL8196EU_4.4.5','/opt/cross-project/mips/realtek/Mips_RTL8196EU_4.4.5/rtl819x/toolchain/rsdk-1.5.5-4181-EB-2.6.30-0.9.30.3-110225/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_GRx389_4.8.1','/opt/cross-project/mips/lantiq/Mips_GRx389_4.8.1/ugw-6.1/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -DIOTC_BIG_ENDIAN -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm_6366_8428P_4.8.3','/opt/cross-project/arm/mstar/Arm_6366_8428P_4.8.3/buildroot-2014.11/bin/arm-buildroot-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm9_Hi3531A_4.8.3','/opt/cross-project/arm/hisilicon/Arm9_Hi3531A_4.8.3/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['ArmCortexA9_S2L55M_4.8.2-test','/opt/cross-project/arm/ambarella/ArmCortexA9_S2L55M_4.8.2-test/linaro-multilib-2013.09-gcc4.8-x86_64/bin/arm-linux-gnueabihf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_GM8139_4.4.0','/opt/cross-project/mips/grainmedia/Mips_GM8139_4.4.0/gm8139_toolchain_pack/toolchain/toolchain_gnueabi-4.4.0_ARMv5TE/usr/bin/arm-unknown-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Mips_RTS3901_4.8.3','/opt/cross-project/mips/realtek/Mips_RTS3901_4.8.3/rts3901_toolchain/toolchain/rsdk-4.8.3-5281-EL-3.10-u0.9.33-m32ut-141222-p160126/bin/mips-linux-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm11_GK7101_4.6.1_Test','/opt/cross-project/arm/gokemicro/Arm11_GK7101_4.6.1_Test/4.6.1/usr/bin/arm-goke-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'],
['Arm11_GK7101_4.6.1_Test2','/opt/cross-project/arm/gokemicro/Arm11_GK7101_4.6.1_Test/4.6.1/usr/bin/arm-goke-linux-uclibcgnueabi-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 --sysroot=/opt/cross-project/arm/gokemicro/Arm11_GK7101_4.6.1_Test/4.6.1/usr/arm-goke-linux-uclibcgnueabi/sysroot/'],
#['Mips_MT7681_4.4.4','/opt/cross-project/mips/mtk/Mips_MT7681_4.4.4/Andes_Linux_BSP_Toolchains/nds32le-elf-newlib-v2j/bin/nds32le-elf-','-x c -fPIC -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS -D__linux__ '],
#['Arm9_Hi3512_3.4.3', '/opt/cross-project/arm/hisilicon/Arm9_Hi3512_3.4.3/Hi3512_gcc-3.4.3-uClibc-0.9.28/bin/arm-hisi-linux-','-x c -s -std=c99 -O2 -Wall -DNOSETCLOCK -D_GNU_SOURCE -DIOTC_NOIFADDRS'],
#['ArmCortexM3_M7A_4.4.1','/opt/cross-project/arm/capital-micro/ArmCortexM3_M7A_4.4.1/linux-cortexm-1.12.0/tools/arm-2010q1/bin/arm-uclinuxeabi-','-x c -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS'],#This toolchain can only build static library.
#['Arm_X_4.8.2','/opt/cross-project/arm/X/Arm_X_4.8.2/linaro-multilib-2013.09-gcc4.8/bin/arm-linux-gnueabihf-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 '],
#['powerpc', "/usr/bin/powerpc-linux-gnu-", '-m32    -g -x c -s -Wvla -std=c99 -O2 -pedantic -Wall -DIOTC_BIG_ENDIAN -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64']  # with Cross Compile
#['powerpc', "", '-m32 -g -x c -s -Wvla -std=c99 -O2 -pedantic -Wall -DIOTC_BIG_ENDIAN -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64'] # on powerpc board
#['Arm_AML8726M3_4.4.3','/opt/cross-project/arm/amlogic/Arm_AML8726M3_4.4.3/bin/arm-linux-androideabi-','-x c -s -std=c99 -O2 -Wall -pedantic -DNOSETCLOCK -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DIOTC_NOIFADDRS --sysroot=/opt/cross-project/arm/amlogic/Arm_AML8726M3_4.4.3/sysroot'], #This toolchain only can build static library
]

# Platform
target = [ i[0] for i in crossinfo ]
# Toolchain path
tcpath = [ i[1] for i in crossinfo ]
# Gcc build flag
ccflag = [ i[2] for i in crossinfo ]

##################################################################################################################
#																												 #
#													Settings													 #
#																												 #
##################################################################################################################
# Common settings
CC = "gcc"
AR = "ar"
AR_FLAG = " -rcs"
SHARE_FLAG = "-fPIC -shared "

# Generate Libraries path
TARGET_BASE_DIR = "../../lib/linux/"

# Include Header path
includepath_pthread =" -I. -I../../../inc  -I../../../iotc/Include -lpthread"
includepath_no_pthread =" -I. -I../../../inc -I../../../iotc/Include "


# kalay_device settings
kalay_device_SRCDIR = " ../../../src/kalay_device/"
kalay_device_SRC = kalay_device_SRCDIR + "kalay_device.c" + kalay_device_SRCDIR + "rdt_daemon.c" + kalay_device_SRCDIR + "jsmn.c"
kalay_device_OBJ = "kalay_device.o rdt_daemon.o jsmn.o"
kalay_device_SHARELIB = "libkalay_device.so"
kalay_device_STATICLIB = "libkalay_device.a"
kalay_device_SHARELIB_D = "libkalay_device.so"
kalay_device_STATICLIB_D = "libkalay_device.a"


# All sources, objects, share libs, static libs
SRC = [kalay_device_SRC]
OBJ = [kalay_device_OBJ]
SHARE_LIB = [kalay_device_SHARELIB]
STATIC_LIB = [kalay_device_STATICLIB]
SHARELIB_WITH_TRACE = [kalay_device_SHARELIB_D]
STATICLIB_WITH_TRACE = [kalay_device_STATICLIB_D]
# All modules
apiSort = ["kalay_device"]

##################################################################################################################
#																												 #
#										Class & Function definition										 		 #
#																												 #
##################################################################################################################

# tcIdx 	: Toolchain index
# moduleIdx : Modulde index
# incPath 	: Include header path
class ThreadParam:
	def __init__(self, tcIdx, moduleIdx, incPath):
		self.tcIdx = tcIdx
		self.moduleIdx = moduleIdx
		self.incPath = incPath
	def getTcIdx(self):
		return self.tcIdx
	def getModuleIdx(self):
		return self.moduleIdx
	def getIncPath(self):
		return self.incPath


# Build Thread
def buildJobThread(*args):
	tcIdx = args[0].getTcIdx()
	moduleIdx = args[0].getModuleIdx()
	includepath = args[0].getIncPath()
	#print("tcIdx = %d, moduleIdx = %d" %(tcIdx ,moduleIdx))
	#print ("[buildJob] - Current thread id : %d" %threading.current_thread().ident)
	#print("export CC='%s' CFLAG='%s' AR='%s' ARFLAG='%s' TARGETDIR='%s' SHAREFLAG='%s' INCLUDE='%s' SRC='%s' OBJ='%s' SHARELIB='%s' STATICLIB='%s'; %s" \
	#				% (tcpath[tcIdx] + CC, ccflag[tcIdx], tcpath[tcIdx] + AR, AR_FLAG, TARGET_BASE_DIR + target[tcIdx], SHARE_FLAG, includepath, SRC[moduleIdx], OBJ[moduleIdx], SHARE_LIB[moduleIdx], STATIC_LIB[moduleIdx], make))
	os.system("export CC='%s' CFLAG='%s' AR='%s' ARFLAG='%s' TARGETDIR='%s' SHAREFLAG='%s' INCLUDE='%s' SRC='%s' OBJ='%s' SHARELIB='%s' STATICLIB='%s' SHARELIB_WITH_TRACE='%s' STATICLIB_WITH_TRACE='%s'; %s" \
					% (tcpath[tcIdx] + CC, ccflag[tcIdx], tcpath[tcIdx] + AR, AR_FLAG, TARGET_BASE_DIR + target[tcIdx], SHARE_FLAG, includepath, SRC[moduleIdx], OBJ[moduleIdx], \
						SHARE_LIB[moduleIdx], STATIC_LIB[moduleIdx], SHARELIB_WITH_TRACE[moduleIdx], STATICLIB_WITH_TRACE[moduleIdx], make))


# Build All modules
def buildJobs(tcIdx, incPath):
	threadList = []
	for j in range(1) :
		print ("\n\t\t(---------- LIB '%s' ----------)" %(SHARE_LIB[j]))
		tParam = ThreadParam(tcIdx, j, incPath)
		threadId = threading.Thread(target=buildJobThread, name="Thread-%s" %(target[tcIdx]), args=(tParam,))
		threadList.append(threadId)
		threadId.start()
	for j in range(1) :
		threadList[j].join()


# Build single module
def buildSingleJob(tcIdx, moduleIdx, incPath):
	print ("\n\t\t(---------- LIB '%s' ----------)" %(SHARE_LIB[moduleIdx]))
	tParam = ThreadParam(tcIdx, moduleIdx, incPath)
	threadId = threading.Thread(target=buildJobThread, name="Thread-%s" %(target[tcIdx]), args=(tParam,))
	threadId.start()
	threadId.join()


def main():
	print "Run main() - Start build libraries"
	# Index of crossinfo array
	toolchainIdx = 0
	includepath = ""
	if platform == "all" :
		for s in target :
			print ("\n\n/********************* Build '%s' **********************/" %(s))
			os.system("mkdir -p '%s%s'" %(TARGET_BASE_DIR, s))

			# Specific Platforms
			if s == "Arm9_AML8723M3_4.6" or s == "Arm_AML8726M3_4.6":
				includepath = includepath_no_pthread
			# Other Platforms
			else :
				includepath = includepath_pthread
			
			buildJobs(toolchainIdx, includepath)
			os.system("make -f Makefile clean")
			toolchainIdx += 1
	else :
		# Specific Platforms
		os.system("mkdir -p '%s%s'" % (TARGET_BASE_DIR, platform))
		if platform == "Arm9_AML8723M3_4.6" or platform == "Arm_AML8726M3_4.6":
			i = target.index(platform)
			includepath = includepath_no_pthread
			if api == "ALL" :	
				buildJobs(i, includepath)
			else :
				j = apiSort.index(api)
				buildSingleJob(i, j, includepath)
			os.system("make -f Makefile clean")
		else :
			# Other Platforms
			i = target.index(platform)
			includepath = includepath_pthread
			if api == "ALL" :
				buildJobs(i, includepath)
			else :
				j = apiSort.index(api)
				buildSingleJob(i, j, includepath)
			os.system("make -f Makefile clean")	
	
################# Setup running parameters Start #################
platform = sys.argv[1]

if platform == "-h" :
	print "./build.py [Platform] [API] [BuildJobs]"
	print "[Platform]:"
	for s in target :
		print ("\t%s" %(s))
	print "[API]:"
	for s in apiSort :
		print ("\t%s" %(s))
	quit()
elif platform == "-p" :
	for s in target :
		print ("%s" %(s))
	quit()
elif platform != "all" :
	#api = sys.argv[2].upper()
	api = sys.argv[2]

if api == "all" :	
	api = "ALL"

if platform != "all" and not( platform in target):
	print ("Platform[%s] is not available !" %(platform))
	quit()

# Increase build speed by using more than one build jobs
if len(sys.argv) > 3 :
	make = "make -f Makefile -j%s" %(sys.argv[3])
else :
	make = "make -f Makefile"
################# Setup running parameters End #################


# Run main here
main()


