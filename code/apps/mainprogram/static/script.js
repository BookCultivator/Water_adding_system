// 模擬一組溫度數據
const temperatureData = [22, 24, 23, 25, 26, 28, 29, 27, 26, 25];
const labels = ['10:00', '10:10', '10:20', '10:30', '10:40', '10:50', '11:00', '11:10', '11:20', '11:30'];

// 顯示最新溫度
const currentTemperature = temperatureData[temperatureData.length - 1];
document.getElementById('current-temperature').textContent = `${currentTemperature} °C`;

// 使用 Chart.js 繪製溫度圖表
const ctx = document.getElementById('temperature-chart').getContext('2d');
new Chart(ctx, {
    type: 'line',
    data: {
        labels: labels,
        datasets: [{
            label: '溫度 (°C)',
            data: temperatureData,
            borderColor: 'rgba(255, 99, 132, 1)',
            backgroundColor: 'rgba(255, 99, 132, 0.2)',
            borderWidth: 2,
            fill: true,
            tension: 0.2
        }]
    },
    options: {
        responsive: true,
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});
