(function($){
  Drupal.behaviors.mymodule = {
    attach: function(context, settings) {
      $(document).ready(function() {
        // CHARTS!! Let's create some charts n graphs!!!
        create_bg_point_chart();
        create_individual_point_chart();
        create_map_number_chart();
        create_explored_bar_chart();


      });

      function create_individual_point_chart() {
        var individual_data = Drupal.settings.mcoc_stats.individual_data;
        var keys = Object.keys(individual_data);
        var data_points = [];

        for (var i = 0; i < keys.length; i++)  {
          data_points[i] =  {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[i]],
            showInLegend: true,
            legendText: keys[i],
          };
        }

        var chart = new CanvasJS.Chart("individualPointChartContainer", {
          animationEnabled: true,
          theme: "light2",
          zoomEnabled: true,
          title: {
            verticalAlign: "top",
            horizontalAlign: "left",
            padding: 15,
            margin: 30
          },
          axisY: {
            titleFontSize: 24,
          },
          axisX: {
            valueFormatString: "DD-MMM" ,
            labelAngle: -37
          },
          legend: {
            cursor: "pointer",
            fontSize: 12,
            itemclick: function (e) {
                if (typeof (e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
                    e.dataSeries.visible = false;
                } else {
                    e.dataSeries.visible = true;
                }

                e.chart.render();
            }
          },
          data: data_points,
        });
        chart.render();
      }

      function create_bg_point_chart() {
        var bg_overall_data = Drupal.settings.mcoc_stats.bg_overall_data;
        var bg_average_data = Drupal.settings.mcoc_stats.bg_average_data;
        var chart = new CanvasJS.Chart("bgPointChartContainer", {
          animationEnabled: true,
          theme: "light2",
          zoomEnabled: true,
          title: {
            verticalAlign: "top",
            horizontalAlign: "left",
            padding: 15,
            margin: 30
          },
          axisY: {
            titleFontSize: 24,
          },
          axisX: {
            valueFormatString: "DD-MMM" ,
            labelAngle: -37
          },
          data: [{
            type: "line",
            xValueType: "dateTime",
            dataPoints: bg_overall_data
          }]
        });
        chart.render();
      }

      function create_map_number_chart() {
        var bg_map_number_datadata = Drupal.settings.mcoc_stats.map_number_data;
        var chart = new CanvasJS.Chart("mapNumberChartContainer", {
          animationEnabled: true,
          data: [{
            type: "pie",
            startAngle: 240,
            yValueFormatString: "##0.00\"%\"",
            indexLabel: "{label} {y}",
            dataPoints: bg_map_number_datadata,
          }]
        });
        chart.render();
      }

      function create_explored_bar_chart() {
        var explored_data = Drupal.settings.mcoc_stats.explored_data;
        var chart = new CanvasJS.Chart("exploredChartContainer", {
          animationEnabled: true,
          theme: "light2", // "light1", "light2", "dark1", "dark2"
          data: [{
            type: "column",
            dataPoints: explored_data,
          }]
        });
        chart.render();
      }

    }
  };
})(jQuery);
