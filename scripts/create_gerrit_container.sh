#!/bin/sh
# This script creates a Gerrit installation and installs all the core plugins
# It assumes that you have right version of java installed on your system. For
# more detailed instructions, please see:
#  https://gerrit-documentation.storage.googleapis.com/Documentation/3.12.2/linux-quickstart.html
export GERRIT_SITE=~/gerrit_testsite
java -jar ~/Downloads/gerrit-3.12.2.war init --batch --dev -d $GERRIT_SITE --install-all-plugins
# Now create a group Students
ssh -p 29418 admin@localhost gerrit create-group Students
