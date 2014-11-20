(function ($) {

  Drupal.behaviors.download_harmonization_table = {
    attach: function (context, settings) {

      $("#download-harmo-table").on('click', function (event) {
        var csv = createCsv(settings.rawData);
        var csvData = 'data:application/csv;charset=utf-8,' + encodeURIComponent(csv);

        $(this)
          .attr({
            'download': settings.dataset.concat('.csv'),
            'href': csvData,
            'target': '_blank'
          });
      });

      function createCsv(data) {
        var headers = data.headers;
        var rows = data.rows;

        var csvRows = headers.join("\t").concat("\r\n");

        $.each(rows, function(i, row){
          csvRows = csvRows.concat(row.join("\t"), "\r\n");
        });

        return csvRows;
      }

    }
  }
}(jQuery));

