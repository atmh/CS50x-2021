import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from flask.helpers import get_flashed_messages
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    users = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])
    owned_cash = users[0]['cash']

    summaries = db.execute("SELECT company, symbol, sum(shares) as sum_of_shares FROM transactions WHERE user_id = ? GROUP BY user_id, company, symbol HAVING sum_of_shares > 0;", session["user_id"])

    # Look up current price of stock
    summaries = [dict(x, **{'price': lookup(x['symbol'])['price']})
                    for x in summaries]

    # Compute total price
    summaries = [dict(x, **{'total': x['price']*x['sum_of_shares']})
                    for x in summaries]

    sum_totals = owned_cash + sum([x['total'] for x in summaries])

    return render_template("index.html", owned_cash=owned_cash, summaries=summaries, sum_totals=sum_totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)
        cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]["cash"]

        if not symbol or price is None:
            return apology("A valid symbol must be provided")

        if not shares:submit50 cs50/problems/2021/x/project
            return apology("A valid share must be provided")

        try:
            shares = int(shares)
            if shares < 1:
                return apology("Share must be a positive whole number")
        except ValueError:
            return apology("Share must be a positive whole number")

        total_price = shares * price["price"]

        query = lookup(symbol)
        price = query["price"]
        name = query["name"]

        if cash < total_price:
            return apology("Insufficient cash")
        else:
            db.execute("INSERT INTO transactions(user_id, company, symbol, shares, price) VALUES(?, ?, ?, ?, ?);", session["user_id"], name, symbol, shares, price)
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", (cash - total_price), session["user_id"])
            flash("Transaction successful")

            return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(row) != 1 or not check_password_hash(row[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = row[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if symbol is None:
            return apology("Valid symbol must be provided")
        return render_template("quote.html", query=symbol)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        row = db.execute("SELECT * FROM users WHERE username = ?", username)

        if not username:
            return apology("Username must be provided")
        elif len(row) != 0:
            return apology("Username already exists")
        elif not password:
            return apology("Password must be provided")
        elif not request.form.get("confirmation"):
            return apology("Confirmation password must be provided")
        elif not password == confirmation:
            return apology("Passwords do not match")

        id = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, id)
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    owned_symbols = db.execute("SELECT symbol, sum(shares) as sum_of_shares FROM transactions WHERE user_id = ? GROUP BY user_id, symbol HAVING sum_of_shares > 0;", session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        try:
            shares = int(shares)
            if shares < 1:
                return apology("Share must be a positive whole number")
        except ValueError:
            return apology("Share must be a positive whole number")

        if not symbol:
            return apology("Symbol missing")

        stocks = {d['symbol']: d['sum_of_shares'] for d in owned_symbols}

        if shares > stocks[symbol] :
            return apology("Insufficient shares")


        query = lookup(symbol)
        price = query["price"]
        name = query["name"]

        shares_value = price * shares

        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        db.execute("INSERT INTO transactions(user_id, company, symbol, shares, price) VALUES(?, ?, ?, ?, ?);", session["user_id"], name, symbol, -shares, price)

        db.execute("UPDATE users SET cash = ? WHERE id = ?;", (rows[0]['cash'] + shares_value), session["user_id"])

        return redirect("/")
    else:
        return render_template("sell.html", symbols=owned_symbols)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
