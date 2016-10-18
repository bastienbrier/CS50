<div>
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
    </ul>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        
        <tbody>
        <?php foreach ($positions as $position): ?>

        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= number_format($position["shares"]) ?></td>
            <td>$<?= number_format($position["price"], 2) ?></td>
            <td>$<?= number_format($position["total"], 2) ?></td>
        </tr>

        <?php endforeach ?>
        
        <tr>
            <td>CASH</td>
            <td> </td>
            <td> </td>
            <td> </td>
            <td>$<?= number_format($cash[0]["cash"], 2) ?></td>
        </tr>
        </tbody>
    </table>
    
</div>

<div>
    <ul class="nav nav-pills">
        <li><a href="password.php">Change Password</a></li>
        <li><a href="logout.php">Log Out</a></li>
    </ul>
</div>
