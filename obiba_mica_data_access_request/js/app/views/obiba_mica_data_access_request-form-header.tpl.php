<?php
/**
 * @file
 * Code for the obiba_mica_data_access_request modules.
 */

?>

<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div>
  <h2 class="page-header">
    <a href="<?php print url(MicaClientPathProvider::DATA_ACCESS_REQUEST, array('fragment' => 'data-access-requests')); ?>"
      title="<?php print variable_get_value('access_my_requests_button'); ?>">
      <i class="glyphicon glyphicon-chevron-left"></i>
    </a>
    <span ng-if="newRequest">
      <?php print t('New') . ' '  . variable_get_value('access_request_page_title'); ?>
    </span>
    <span ng-if="!newRequest">
      <?php print t('Edit') . ' ' . variable_get_value('access_request_page_title'); ?>: {{requestId}}
    </span>
  </h2>

</div>