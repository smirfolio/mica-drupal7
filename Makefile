help:
	@echo
	@echo "Mica Drupal 7 Client"
	@echo
	@echo "Available make targets:"
	@echo "  all          : Clean & setup Drupal with Mica modules in target directory"
	@echo "  setup-drupal : Setup Drupal with Mica modules in target directory"
	@echo "  copy-mica    : Copy Mica modules to Drupal instance in target directory"
	@echo

all: clean setup-drupal

clean:
	rm -rf target

setup-drupal:
	drush make drupal/drupal-basic.make target/drupal && \
	cp -r drupal/modules/* target/drupal/sites/all/modules

copy-mica:
	cp -r drupal/modules/* target/drupal/sites/all/modules
