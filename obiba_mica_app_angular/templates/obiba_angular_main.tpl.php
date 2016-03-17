<?php
/**
 * @file
 * Code for the obiba_mica_app_angular modules.
 */

?>
<?php if(!empty($node_page)):?>
<?php print render($node_page) ?>
<?php endif; ?>
  <obiba-alert id="MainController"></obiba-alert>
  <div ng-controller="NotificationController"></div>
  <div ng-view=""></div>
