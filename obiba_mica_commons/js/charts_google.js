/**
 * @file
 * JavaScript integration between Google Charts and Drupal.
 */
(function ($) {

  Drupal.behaviors.chartsGoogle = {};
  Drupal.behaviors.chartsGoogle.attach = function (context, settings) {

    /**
     * Helper function to load the Google chart API dynamically so as to have control on when to start rendering the
     * charts. This is not a guaranteed solution under Chrome where there sporadic exceptions occur!
     *
     * @param onDoneCallback
     */
    function loadGoogleChartApi(onDoneCallback) {

      function canExecute() {
        return (typeof google !== 'undefined' && google.load);
      }

      function execute() {
        if (canExecute()) {
          if (onDoneCallback) {
            onDoneCallback();
          }
        } else {
          console.error("Failed to load https://www.google.com/jsapi.");
        }
      }

      if (canExecute()) {
        execute();
        return;
      }

      $.getScript("https://www.google.com/jsapi")
        .done(function(){
          execute();
        })
        .fail(function() {
          console.error("Failed to load https://www.google.com/jsapi.");
        });
    }

    /**
     * Sets some callbacks, loades the grphic packages and renders the charts
     */
    function initAndRenderCharts() {
      // First time loading in Views preview may not work because the Google JS
      // API may not yet be loaded.
      if (typeof google !== 'undefined') {
        google.load('visualization', '1', {callback: renderCharts});
      }

      // Redraw charts on window resize.
      var debounce;
      $(window).resize(function () {
        clearTimeout(debounce);
        debounce = setTimeout(function () {
          $('.charts-google').each(function () {
            var wrap = $(this).data('chartsGoogleWrapper');
            if (wrap) {
              wrap.draw(this);
            }
          });
        }, 75);
      });

      function renderCharts() {
        $('.charts-google').once('charts-google', function () {
          if ($(this).attr('data-chart')) {
            var config = $.parseJSON($(this).attr('data-chart'));
            var wrap = new google.visualization.ChartWrapper();
            wrap.setChartType(config.visualization);
            wrap.setDataTable(config.data);
            wrap.setOptions(config.options);
            // Apply data formatters. This only affects tooltips. The same format is
            // already applied via the hAxis/vAxis.format option.
            var dataTable = wrap.getDataTable();
            if (config.options.series) {
              for (var n = 0; n < config.options.series.length; n ++) {
                if (config.options.series[n]['_format']) {
                  var format = config.options.series[n]['_format'];
                  if (format['dateFormat']) {
                    var formatter = new google.visualization.DateFormat({pattern: format['dateFormat']});
                  }
                  else {
                    var formatter = new google.visualization.NumberFormat({pattern: format['format']});
                  }
                  formatter.format(dataTable, n + 1);
                }
              }
            }

            // Apply individual point properties, by adding additional "role"
            // columns to the data table. So far this only applies "tooltip"
            // properties to individual cells. Ideally, this would support "color"
            // also. Feature request:
            // https://code.google.com/p/google-visualization-api-issues/issues/detail?id=1267
            var columnsToAdd = {};
            var rowCount = dataTable.getNumberOfRows();
            var columnCount = dataTable.getNumberOfColumns();
            for (var rowIndex in config._data) {
              if (config._data.hasOwnProperty(rowIndex)) {
                for (var columnIndex in config._data[rowIndex]) {
                  if (config._data[rowIndex].hasOwnProperty(columnIndex)) {
                    for (var role in config._data[rowIndex][columnIndex]) {
                      if (config._data[rowIndex][columnIndex].hasOwnProperty(role)) {
                        if (! columnsToAdd[columnIndex]) {
                          columnsToAdd[columnIndex] = {};
                        }
                        if (! columnsToAdd[columnIndex][role]) {
                          columnsToAdd[columnIndex][role] = new Array(rowCount);
                        }
                        columnsToAdd[columnIndex][role][rowIndex] = config._data[rowIndex][columnIndex][role];
                      }
                    }
                  }
                }
              }
            }
            // Add columns from the right-most position.
            for (var columnIndex = columnCount; columnIndex >= 0; columnIndex --) {
              if (columnsToAdd[columnIndex]) {
                for (var role in columnsToAdd[columnIndex]) {
                  if (columnsToAdd[columnIndex].hasOwnProperty(role)) {
                    dataTable.insertColumn(columnIndex + 1, {
                      type: 'string',
                      role: role
                    });
                    for (var rowIndex in columnsToAdd[columnIndex][role]) {
                      dataTable.setCell(parseInt(rowIndex) - 1, columnIndex + 1, columnsToAdd[columnIndex][role][rowIndex]);
                    }
                  }
                }
              }
            }

            function selectHandler() {
              var selectedItem = wrap.getChart().getSelection()[0].row + 1;
              if (selectedItem) {
                window.location.href = Drupal.settings.basePath + Drupal.settings.chartSettings.searchPath +
                  config.options.links[wrap.getChart().getSelection()[0].column - 1][wrap.getChart().getSelection()[0].row];
              }
            }

            wrap.draw(this);
            google.visualization.events.addListener(wrap, 'select', selectHandler);
            $(this).data('chartsGoogleWrapper', wrap);
          }
        });
      }
    }

    // loading and render charts
    loadGoogleChartApi(initAndRenderCharts);
  };

})(jQuery);
