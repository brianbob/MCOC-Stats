(function($){
  Drupal.behaviors.mymodule = {
    attach: function(context, settings) {
      $(document).ready(function() {
        // CHARTS!! Let's create some charts n graphs!!!
        create_bg_point_chart();
        create_individual_point_chart();
        create_map_number_chart();


      });

      function create_individual_point_chart() {
        var individual_data = Drupal.settings.mcoc_stats.individual_data;
        var keys = Object.keys(individual_data);
        //console.log(individual_data);
        //console.log(keys);
        //console.log(individual_data[keys[0]]);
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
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[1]],
            showInLegend: true, 
            legendText: keys[1],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[2]],
            showInLegend: true, 
            legendText: keys[2],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[3]],
            showInLegend: true, 
            legendText: keys[3],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[4]],
            showInLegend: true, 
            legendText: keys[4],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[5]],
            showInLegend: true, 
            legendText: keys[5],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[6]],
            showInLegend: true, 
            legendText: keys[6],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[7]],
            showInLegend: true, 
            legendText: keys[7],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[8]],
            showInLegend: true, 
            legendText: keys[8],
          },
          {
            type: "line",
            xValueType: "dateTime",
            dataPoints: individual_data[keys[9]],
            showInLegend: true, 
            legendText: keys[9],
          },
        ]
        });
        chart.render();
      }

      function create_bg_point_chart() {
        var bg_data = Drupal.settings.mcoc_stats.bg_data;
        console.log(bg_data);
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
            dataPoints: bg_data
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
    }
  };
})(jQuery);