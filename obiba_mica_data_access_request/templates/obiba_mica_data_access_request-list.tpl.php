<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div ng-app="DataAccessRequest">
  <?php $can_access = obiba_mica_data_access_request_user_permission(MicaDataAccessRequest::NEW_DATA_ACCESS);
  if ($can_access) {
    print l('<i class="fa fa-plus"></i> ' . t(variable_get_value('access_new_request_button')), 'mica/data-access/request', array(
        'html' => TRUE,
        'fragment' => '/new',
        'attributes' => array(
          'class' => array('btn', 'btn-info'),
          'id' => 'new-data-access-request'
        )
      )
    );
  } ?>

  <table class="table table-striped" id="table-requests"></table>

  <div class="modal fade" id="delete-modal" tabindex="-1" role="dialog"
    aria-labelledby="myModalLabel"
    aria-hidden="true">
    <div class="modal-dialog">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal"
            aria-label="Close"><span
              aria-hidden="true">&times;</span></button>
          <h4 class="modal-title" id="myModalLabel"><i
              class="fa fa-exclamation-triangle"></i> <?php print t('Delete Data Access Request'); ?>
          </h4>
        </div>
        <div class="modal-body">
          <p><?php print t('Are you sure you want to delete Data Access '); ?> '<span
              id="data-access-title"></span>'
            <?php print t('requested by'); ?>
            '<span id="data-access-applicant"></span>'?
          </p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default"
            data-dismiss="modal"><?php print t('Cancel'); ?>
          </button>
          <button id="clickedDelete" type="button" class="btn btn-primary"
            data-delete-resource=""><?php print t('Ok'); ?>
          </button>
        </div>
      </div>
    </div>
  </div>

  <div class="modal fade" id="UserDetailModal" tabindex="-1" role="dialog"
    aria-labelledby="UserDetailModal">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal"
            aria-label="Close"><span
              aria-hidden="true">&times;</span></button>
          <h4 class="modal-title"
            id="UserDetailModalTilte"><?php print t('Applicant profile'); ?></h4>
        </div>
        <div class="modal-body">
          <div>
            <label for="recipient-name"
              class="control-label"><?php print t('Name Applicant : '); ?></label>
            <span id="data-name-applicant"></span>
          </div>

          <div>
            <label for="recipient-email"
              class="control-label"><?php print t('E-mail Applicant : '); ?></label>
            <span id="data-email-applicant"></span>
          </div>
          <div id="user-attributes">

          </div>
          <a id="data-email-applicant" class="btn btn-default" href=""
            target="_blank"><?php print t('Send a mail to this applicant'); ?></a>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">
            Close
          </button>
        </div>
      </div>
    </div>
  </div>

</div>
