# README

## Setup Instructions

1. Clone the repo using the following command `git clone https://github.com/GuelphOntologyTeam/Backend.git`

2. Make sure the repo is somewhere with apache 2.0 and PHP 7 enabled such as /var/www/html/ on linux machines or /Library/WebServer/Documents/ on mac

3. In the root directory run `composer install`

4. Update the config/configFile.php with the correct information to connect to a database and the encrptoion key that you are using

5. You should now be all setup to start using the API and making queries to it. Please refer to the Wiki on github to see a list of available querries you can make to the API. (https://github.com/GuelphOntologyTeam/Backend/wiki/API-Endpoints)



## Don't have composer?

Run the following command to setup a instance of composer. Please be sure you are inside of the backendTOE directory before doing this.

php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"

php -r "if (hash_file('SHA384', 'composer-setup.php') === 'e115a8dc7871f15d853148a7fbac7da27d6c0030b848d9b3dc09e2a0388afed865e6a3d6b3c0fad45c48e2b5fc1196ae') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;"

php composer-setup.php

Once you have run all 3 of these commands you will now have a file called composer.phar so as stated above you need to run composer install in this case you will run the following:

`./composer.phar install`

This is the same as running `composer install`.
