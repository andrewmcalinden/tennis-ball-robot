#!/bin/bash

# Copyright (c)2010-2012 rbTechnologies, LLC
# By Rubin Bennett rbennett@rbtechvt.com>
# modified by Jan Balewski, 2013 : toggel u+w for the /etc/shadow 

# Released under the terms and conditions of the GNU Public License version 2.

# A simple script to assist in server migrations from Linux to Linux
# Intended to be run on the NEW server, and expecting that you have performed
# ssh key exchange for password-less login to the OLD server (or type OLD root pass 3x)

# Note,  Limits according to different Linux distro:
#  RHEL/CentOS/Fedora Core : Default is 500 and upper limit is 65534 (/etc/libuser.conf).
#  Debian and Ubuntu Linux : Default is 1000 and upper limit is 29999 (/etc/adduser.conf).

# IP address or hostname of source server (e.g. server your're migrating AWAY from
sourceServer=192.168.146.167
export UGIDLIMIT=500

# name of generic user on NEW system whose home dir will be used as template for all added users
templateUser=jas


function syncusers() {
    echo you will need to enter 3x  root password for the OLD system
    echo 1 acquire OLD passwd ...
        #scp $sourceServer:/etc/passwd /tmp/passwd.$sourceServer
    echo 2 acquire OLD group ...
        #scp $sourceServer:/etc/group /tmp/group.$sourceServer
    echo 3 acquire OLD shadow ...
        #scp $sourceServer:/etc/shadow /tmp/shadow.$sourceServer
    echo that is all on the OLD system
    
        # First, make a list of non-system users that need to be moved.
    
    awk -v LIMIT=$UGIDLIMIT -F: '($3 >= LIMIT) && ($3 != 65534)' /tmp/passwd.$sourceServer > /tmp/passwd.mig
    awk -v LIMIT=$UGIDLIMIT -F: '($3 >= LIMIT) && ($3 != 65534)' /tmp/group.$sourceServer >/tmp/group.mig
    awk -v LIMIT=$UGIDLIMIT -F: '($3 >= LIMIT) && ($3 != 65534) { print $1 }' /tmp/passwd.$sourceServer  | tee - |egrep -f - /tmp/shadow.$sourceServer > /tmp/shadow.mig
    awk -v LIMIT=$UGIDLIMIT -F: '($3 >= LIMIT) && ($3 != 65534) { print $1":" }' /tmp/passwd.$sourceServer | tee - |egrep -wf - /tmp/shadow.$sourceServer > /tmp/shadow.mig
    
    exists=$(grep $templateUser /tmp/passwd.mig)
    if [ "$exists" ]
	then
	  echo "Conflict of user names, templet user=$exists  also exist on the old system, abort"
	  exit 1
      fi


    echo "Now copy non-duplicate entries in to the new server files..."
    while IFS=: read user pass uid gid full home shell
      do
      line="$user:$pass:$uid:$gid:$full:$home:$shell"
      exists=$(grep $user /etc/passwd)
      if [ -z "$exists" ]
	  then
	  echo "Copying entry for user $user to new system"
	  echo $line >> /etc/passwd
      fi
      
    done </tmp/passwd.mig
    
    while IFS=: read group pass gid userlist
      do
      line="$group:$pass:$gid:$userlist"
      exists=$(grep $group /etc/group)
      if [ -z "$exists" ]
	  then
	  echo "Copying entry for group $group to new system"
	  echo $line >> /etc/group
      fi
    done </tmp/group.mig
    
    # temporarlity add write privileges to the shadow file
    chmod u+w /etc/shadow
    
    while IFS=: read user pass lastchanged minimum maximum warn
      do
      line="$user:$pass:$lastchanged:$minimum:$maximum:$warn"
      exists=$(grep $user /etc/shadow)
      
      if [ -z "$exists" ]
	  then
	  echo "Copying entry for user $user to new system"
	  echo $line >> /etc/shadow
      fi
    done </tmp/shadow.mig
    chmod u-w /etc/shadow

    echo "create home dirs for all users"
    while IFS=: read user pass uid gid full home shell
      do
      line="$user:$pass:$uid:$gid:$full:$home:$shell"
      #echo u=$user h=$home
      if [ -d "$home" ] ;	  then
	  echo "skip exiting $home"; continue;
      fi
      userGrp=`grep $user /etc/group| cut -f1 -d:`      
      echo clone $home:$userGrp from $templateUser       
      cp -rp /home/$templateUser $home
      chown -R $user:$userGrp $home
    done </tmp/passwd.mig
    


}

#---------------------  MAIN -----------------

 

echo "Copying user accounts and passwords from IP=$sourceServer , template new user=$templateUser"

echo -n "Do you have backups of your existing passwd files? [y|N] "
read
if [ "$REPLY" != "y" ]
    then
    echo "Please back your files up and run this script again, abort"
    exit 1
fi


syncusers

exit 0