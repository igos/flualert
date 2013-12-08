The application environment

You may note that the application environment constant value looks for an environment variable “APPLICATION_ENV”. We recommend setting this in your web server environment. In Apache, you can set this either in your vhost definition, or in your .htaccess file. We recommend the following contents for your public/.htaccess file:

<code>
RewriteEngine on

# Set Yii environment:
SetEnv APPLICATION_ENV development
#SetEnv APPLICATION_ENV staging
#SetEnv APPLICATION_ENV test
#SetEnv APPLICATION_ENV production

RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_FILENAME} !-d

RewriteRule . index.php
</code>