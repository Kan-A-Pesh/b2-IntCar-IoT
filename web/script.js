async function send(index, value) {
    console.log("http://172.20.10.2/" + index + "/" + value);
    try {
        await fetch("http://172.20.10.2/" + index + "/" + value, {
            method: "POST",
        });
    } catch (e) {
        console.error(e);
    }
    return;
}

(async () => {
    await send(0, "A");
    await send(9, "S");
    await send(10, "F");
    await send(11, "0");
})();

const alphabet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"];

function getLetterByPercent(percent) {
    const amount = Math.floor(percent / -10);
    return alphabet[amount];
}

document.getElementById("direction").addEventListener("input", function () {
    if (this.value < 0) {
        return send(9, getLetterByPercent(this.value));
    }
    return send(9, this.value);
});

document.getElementById("speed").addEventListener("input", function () {
    const value = Math.floor(this.value * 10);
    if (value < 10) {
        return send(11, value);
    } else {
        return send(11, "F");
    }
});

document.getElementById("forward").addEventListener("click", function () {
    send(10, "F");
});

document.getElementById("backward").addEventListener("click", function () {
    send(10, "B");
});

document.getElementById("disabled").addEventListener("click", function () {
    send(10, "D");
});
