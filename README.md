# Mica Drupal 7 Client

[Drupal 7](https://drupal.org) client for [Mica Server](https://github.com/obiba/mica-server).

## For developers

Use Makefile to build and run the project: `make help`

Run `make all` to:

* clear `target` dir
* download Drupal instance to `target` dir and configure it with `drupal/dev/settings.php`
* drop and import `drupal` database based on `drupal/drupal-7.27.sql`
* create a symlink `/var/www/drupal` pointing to `target/drupal`

Use **administrator** / **password** to login into your new Drupal:
[http://localhost/drupal](http://localhost/drupal)

## Sponsors

Tested with [![BrowserStack](https://cdn2.browserstack.com/production/images/layout/logo-header.png)](http://www.browserstack.com)

