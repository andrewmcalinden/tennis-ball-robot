#!/bin/bash
# default params
ARGV0=`basename $0`
CWD=`pwd`

codeVer=-1
facility=x
action=x
EBSdisk=x
WRKdisk=x

usage()
{
    echo $*
    echo "usage $argv0 -v nn -D/P [options] "
    echo "options are: "
    echo "   -h           : this help"
    echo "   -D/P/T/U       : action: Deploy (from archive).  Pack (to archive), Transfer to RCF, Upload to node"
    echo "   -v nn        : code version [$codeVer]"
    echo "   -f [lra]     : facility: local, rcf, amazon"
    echo " "
}

TEMP=`getopt -n $ARGV0 -- hf:ZDPTv:U  $*`
if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi
eval set -- "$TEMP"
while true ; do
    case "$1" in
        -h)#.......................... HELP
            usage
            exit 0
            shift ;;

        -Z)#.......................... SETUP mappres/reducers
	    nMAPP=`echo $2 | cut -f1 -d.`
	    nREDU=`echo $2 | cut -f2 -d.`
            echo JSET: nMapp=$nMAPP  nRedu=$nREDU
            shift 2 ;;

        -D)#.......................... Action deploy
	    action=deploy
            shift   ;;

        -P)#.......................... Action pack
	    action=pack
            shift   ;;

        -T)#.......................... Action transfer
	    action=transfer
            shift   ;;

	-U)#.......................... Action Upload to node
	    action=upload
            shift   ;;

	-f)#.......................... FACILITY dependent 
	    facility=$2
            shift  2 ;;

	-v)#.......................... code VERSION
	    codeVer=$2
            shift  2 ;;

         --)
            shift
            break 2 ;;
        *) 
	    usage; echo "Internal error!" ; exit 1 ;;
    esac
done


#---------- VERIFY CONSISTENCY OF THE TASK -----

if [ $facility = "l" ] ; then 
    facility=laptop
    EBSdisk=/tmp
    WRKdisk=/tmp
elif [ $facility = "a" ] ; then 
    facility=amazon
    EBSdisk=/storage
    WRKdisk=/mnt
elif [ $facility = "r" ] ; then 
    facility=rcf
    EBSdisk=/tmp
    WRKdisk=/tmp

else
   usage; echo   "specify Facility=$facility ? , abort"; exit 1;
fi

if [  $action = deploy -o $action = pack  ] ; then
    if [ $codeVer -lt 1 ] ; then 
	echo specify  codeVer=$codeVer , abort $action
	exit 1
    fi
fi


echo Final selection: codeVer=$codeVer facility=$facility bigPath=$bigPath



#----------- D E P L O Y ------------------------

if [ $action = "deploy" ] ; then 
    echo "Action=deploy, use archive, ssh to deltag5...";
    arcCode=packV$codeVer.tar
    scp  balewski@deltag5.lns.mit.edu:"0x/$arcCode" .    
    if [ $? -ne 0  ]; then echo "ssh failed, abort" ; exit 1; fi
    ls -l $arcCode
    if [ $? -ne 0  ]; then echo "bad tar-ball, abort" ; exit 1; fi

    #.... unpack & rename the tar-bal
    tar -xf  $arcCode
    newVer=`expr $codeVer + 1`
    echo $codeVer $newVer
    mv packV$codeVer packV$newVer
    cd packV$newVer
    if [ $? -ne 0  ]; then echo "fail to unpack, abort" ; exit 1; fi
    ls -l .

    #... special case
    if [ ! $facility = "amazon" ] ; then
	    mkdir $EBSdisk/iter
    fi


    #... create dirs for wrk & data
    mkdir $WRKdisk/janWrk
    ln -s $WRKdisk/janWrk ../wrk
    cd  $EBSdisk/iter
    pwd
    if [ $? -ne 0  ]; then echo "bigData dir not avaliable, abort" ; exit 1; fi

    #wget http://harvard-cs264.s3.amazonaws.com/scowiki-20090929-one-page-per-line.gz 
    #gunzip scowiki-20090929-one-page-per-line.gz 
    #mv scowiki-20090929-one-page-per-line wS-pages-raw    

    df -h .
    #ls -l $EBSdisk/iter/wS-pages-raw
    #cat $EBSdisk/iter/wS-pages-raw |wiki2mappPR.py >$EBSdisk/iter/wS-pages-iter0
    echo
    echo for testing execute hadoop :
    echo cd packV$newVer/ 
    echo ./runPageRank.sh -E -X -w -D 4.2 -m -I 0.3 -i -f

    exit 0;
fi

#----------- T R A N S F E R ------------------------

if [ $action = "transfer" ] ; then 
    echo "Action=transfer data ..."
    cd  $bigPath/input
    #    fileN=wS-pages
    fileN=wL3-pages-raw
    hadoop fs -ls $fileN 
    hadoop fs -get $fileN .
    outPath=/star/data05/scratch/balewski/ec2Test1
    scp -i ~/.ec2/id_rsa-janBNL $fileN balewski@rftpexp.rhic.bnl.gov:"$outPath"
    # ssh -i id_rsa-janBNL balewski@rftpexp.rhic.bnl.gov
    echo transfer done
    exit 0;
fi

#----------- U P L O A D  ------------------------

if [ $action = "upload" ] ; then 
    echo "Action=upload data to node"
    cd  $bigPath/input
    if [ $? -ne 0  ]; then echo "input dir not accessible, abort" ; exit 1; fi


    #..... wiki-medium...    
    if [ 0 -eq 1 ] ; then
    wget http://harvard-cs264.s3.amazonaws.com/afwiki-20091002-one-page-per-line.gz
    gunzip afwiki-20091002-one-page-per-line.gz
    if [ $? -ne 0  ]; then echo "failed unpack wiki-mid, abort" ; exit 1;   fi
    date
    echo uploading wiki-med to hadoop HDFS ...
    mv afwiki-20091002-one-page-per-line wM-pages
    hadoop fs -put wM-pages wM-pages-raw
    if [ $? -ne 0  ]; then echo "failed uplad wiki-mid to HDFS, abort" ; exit 1;   fi
    date
    fi # end of wiki-med


    #..... wiki-large-2 ...
    if [ 1 -eq 1 ] ; then
    wget http://harvard-cs264.s3.amazonaws.com/enwiki-20090929-one-page-per-line-part2.gz
    date
    echo unzip wiki-L2 ...
    gunzip enwiki-20090929-one-page-per-line-part2.gz
    if [ $? -ne 0  ]; then echo "faild wiki-L2, abort" ; exit 1;   fi
    date
    echo uploading wiki-med to hadoop HDFS ...
    mv enwiki-20090929-one-page-per-line-part2 wL2-pages
    hadoop fs -put    wL2-pages  wL2-pages-raw
    if [ $? -ne 0  ]; then echo "failed uplad wiki-L2 to HDFS, abort" ; exit 1;   fi
    fi # end of wiki-L2
    date



    #..... wiki-large-3 ...
    if [ 0 -eq 1 ] ; then
    wget http://harvard-cs264.s3.amazonaws.com/enwiki-20090929-one-page-per-line-part3.gz
    date
    echo unzip wiki-L3 ...
    gunzip enwiki-20090929-one-page-per-line-part3.gz
    if [ $? -ne 0  ]; then echo "faild wiki-L3, abort" ; exit 1;   fi
    date
    echo uploading wiki-med to hadoop HDFS ...
    mv enwiki-20090929-one-page-per-line-part3 wL3-pages
    hadoop fs -put    wL3-pages  wL3-pages-raw
    if [ $? -ne 0  ]; then echo "failed uplad wiki-L3 to HDFS, abort" ; exit 1;   fi
    fi # end of wiki-L3
    date

    exit 0
fi


#----------- P A C K  ------------------------

if [ $action = "pack" ] ; then 
    echo "Action=pack  ssh to deltag5...";
    arcCode=packV$codeVer
    ls -l $arcCode
    if [ $? -ne 0  ]; then echo "bad source dir, abort" ; exit 1; fi

    #.... pack  the tar-bal
    rm -f $arcCode.tar
    tar -cf  $arcCode.tar $arcCode

    echo "scp  $arcCode.tar to deltag5 ..."
    scp -p $arcCode.tar $ARGV0  balewski@deltag5.lns.mit.edu:0x    
    if [ $? -ne 0  ]; then echo "ssh failed, abort" ; exit ;	
    fi
    echo tar ball archived
    exit 
fi

echo "specify action, abort"; exit 1;

