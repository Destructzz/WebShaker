LoadSettingsFromServer();

async function SendToServer() {
    const text = document.getElementById('text').value;

    // Создаём объект с данными для отправки
    const data = {
        text: text
    };

    // Отправка POST-запроса
    const response = await fetch('http://localhost:8080/SendToServer', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)  // Преобразуем объект в JSON-строку
    });

    const result = await response.json();  // Читаем ответ от сервера как JSON
    console.log(result["response"]);
}

async function LoadSettingsFromServer() {

    try{
        const response = await fetch('http://localhost:8080/get_settings');
        const data = await response.json();

        document.getElementById('x-input').value = data["x"];
        document.getElementById('y-input').value = data["y"];
        document.getElementById('speed-input').value = data["s"];
    }
    catch(error){
        console.error("Ошибка получения координат", error);
    }

}


async function LoadSettingsToServer(newX, newY, newS) {
    const X = document.getElementById('x-input').value;
    const Y = document.getElementById('y-input').value;
    const S = document.getElementById('speed-input').value;

    const response = await fetch('http://localhost:8080/update_coordinates',{
        method : 'POST',
        headers : {
            'Content-type' : 'application/json',
        },
        body : JSON.stringify({
            x: newX,
            y: newY,
            s: newS
        })
    });
    const result = response.json();
    console.log(result["response"]);
}


const button = document.getElementById('apply');

button.addEventListener('click', ()=> {
    LoadSettingsToServer(document.getElementById('x-input').value, document.getElementById('y-input').value, document.getElementById('speed-input').value);
});