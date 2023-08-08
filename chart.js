let label = [];
let data1 = [];
let data2 = [];

const chartdata = {
  labels: label,
      datasets: [{
          label: 'Present Temperature',
          backgroundColor: 'orange',
          borderColor: 'black',
          data: data1
      },
      {
        label: 'Prediction(Forecast) Temperature',
        backgroundColor: 'pink',
        borderColor: 'black',
        data: data2
      },
    ]
   
  };
  const config = {
      type: 'bar',
      data: chartdata,
      options:{}
  };
  var myChart = new Chart(
      document.getElementById('myChart'),
      config
  );
// load data to database
$(document).ready(function() {
  updateChart();
});
setInterval(updateChart,1000);
function updateChart (){
  $.post('temp.php', function(data){
    let label = [];
    let data1 = [];
    let data2 = [];
    // how to get one old_temp and new_temp which get before(old_temp)
    for(let i in data){
        label.push('ID: ' + data[i].id);
        data1.push(data[i].data);
        if(i>0)
        {
          data2.push(data1[i]);
        }
    }
    myChart.data.labels = label;
    myChart.data.datasets[0].data = data1;
    myChart.data.datasets[1].data = data2;
    myChart.update();


    });

}



