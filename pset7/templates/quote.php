<p>
    A share of <?= htmlspecialchars($stock["name"]) ?> (<?= htmlspecialchars($stock["symbol"]) ?>) 
    costs <b>$<?= htmlspecialchars(number_format($stock["price"], 2)) ?></b>
</p>
