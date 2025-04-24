function getHi(id) {
    fetch('/IOT/IoT_page/' + id)
        .then(response => response.json())
        .then(data => {
            document.getElementById('output').innerText = data.message;
        });
    }