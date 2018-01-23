(function($){
  Drupal.behaviors.mymodule = {
    attach: function(context, settings) {
      $(document).ready(function() {
        // CHARTS!! Let's create some charts n graphs!!!
        create_individual_point_chart();


      });

      function create_individual_point_chart() {
        var individual_data = Drupal.settings.mcoc_stats.individual_data;
        var keys = Object.keys(individual_data);

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
                //console.log("legend click: " + e.dataPointIndex);
                //console.log(e);
                if (typeof (e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
                    e.dataSeries.visible = false;
                } else {
                    e.dataSeries.visible = true;
                }

                e.chart.render();
            }
          },
          data: [
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[0]],
            showInLegend: true, 
            legendText: keys[0],
          },
         
        ]
        });
        chart.render();
      }
    }
  };
})(jQuery);