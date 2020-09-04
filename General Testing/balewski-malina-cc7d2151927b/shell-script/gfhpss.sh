#!/bin/bash
argv0=`basename $0`
version=3.1
debug=0
update=0
run=-1
year=2005
action=get
url="http://online.star.bnl.gov/RunLog$year/Summary.php3"
destdir=`pwd`
starsink="/home/starsink/raw/daq/$year"
hpsslist=list.hpss
extraopt=""

% find . -name '*.ps' -exec gzip {} \; % find . -name '*.eps' -exec gzip
{} \;

# check for Hess
/usr/bin/which hpss_user.pl  2> /dev/null > /dev/null
if [ $? -ne 0  ]; then echo "hpss_user.pl not found" ; exit 1; fi
# check for lynx
#/usr/bin/which lynx          2> /dev/null > /dev/null
#if [ $? -ne 0  ]; then echo "lynx program not found" ; exit 1; fi
# check for rftp
/usr/bin/which rftp 2> /dev/null > /dev/null
if [ $? -ne 0  ]; then echo "rftp program not found" ; exit 1; fi

temp=`getopt -n $argv0 -- l:cdufh $*`
if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

usage() 
{
    echo $*
    echo "usage $argv0 [options] run_number"
    echo "options are: "
    echo "   -c           : check if files are present"     
    echo "   -d           : turn on debugging (dry run)"     
    echo "   -u           : turn on update mode"     
    echo "   -h           : this help"
    echo " "
    echo "$argv0 version $version"
}

eval set -- "$temp"
while true ; do
    case "$1" in
	-c)
	    action=check
	    shift  ;;
	-d)
	    debug=1;
	    shift ;;
	-u)
	    update=1;
	    shift ;;
	-h)
	    usage
	    exit 0
	    shift ;;
        --)
            shift
            break;;
        *)
            echo "Internal error!" ; exit 1 ;;
    esac
done

run=$*
if [ -z "$run" ] ; then usage ; exit 1; fi


#
base=$[ ( $run / 1000 ) % 1000 ]
if [ $base -lt 100 ] ; then base="0$base" ; fi
if [ $base -lt  10 ] ; then base="0$base"; fi
# 

echo run=$run
ftplist=$run.ftp
get_file_list.pl -keys filename -cond runnumber=$run  -limit 10000 | grep daq > $ftplist 


filelist=`grep ${run} ${ftplist} | awk '{print $1 ":"}'`

if [ -f "${filelist}" ]; then
   echo "file list in ${ftplist} is empty" 
   exit 1   
fi
#

#
case "$action" in
	get)
	hpsslist=$run.hpss
	rm -f $hpsslist
	# make the list
	for line in $filelist; do
	    #echo $line 
	    adc=`echo $line | grep adc `
	    #if [ -z "$adc" ]; then continue; fi
	    fn=`echo $line | cut -f1 -d:`
	    sz=`echo $line | cut -f2 -d:` sz=`echo $line | cut -f2 -d:`
	    #echo "fn=$fn  sz=$sz adc=$adc"
	    echo $starsink/$base/$fn $destdir/$fn >> $hpsslist
	done
	if [ $debug  -gt 0 ]; then extraopt="-k   $extraopt"; fi
	if [ $update -gt 0 ]; then extraopt="-upd $extraopt"; fi
	echo hpss_user.pl $extraopt -f $hpsslist
	;;
	check)
	nmissing=0
	for line in $filelist; do
    	    fn=`echo $line | cut -f1 -d:`
	    sz=`echo $line | cut -f2 -d:`
	    echo -n "$fn: "
	    if [ -f $destdir/$fn ]; then
	        rz=`ls -l $destdir/$fn | awk '{ print $5 }'` 
	        if [ -z "$rz" ]; then rz=0; fi
		if [ $rz -eq $sz ]; then 
		   echo "OK (size=$rz)"
		else
		   nmissing=$[ $nmissing + 1 ]
		   echo "is being restored"
		fi
	    else
		nmissing=$[ $nmissing + 1 ]
		echo "not yet restored"
	    fi
	done
	if [ $nmissing -eq 0 ]; then
	  echo "all files are restored"
	else
	  echo "missing $nmissing file(s)"
	fi
	;;
	*)
	;;
esac
#rm -f $hpsslist

git clone  https://balewski@bitbucket.org/balewski/vm-condor.git