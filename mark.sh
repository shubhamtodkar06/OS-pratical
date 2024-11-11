#!/bin/bash

address_book="address.txt"

create() {
    >"$address_book"
    echo "New Address Book is created."
}

view() {
    if [ -s "$address_book" ]; then
        cat "$address_book"
    else
        echo "Address book is empty."
    fi
}

insert() {
    echo "Enter following details : "
    echo "Name :"
    read name
    echo "Phone :"
    read phone
    echo "Enter Email :"
    read email
    echo "$name | $phone | $email" >> "$address_book"
    echo "Record added."
}

delete() {
    echo "Enter name or phone or email to delete record: "
    read value
    if grep -q "$value" "$address_book"; then
        grep -v "$value" "$address_book" > temp && mv temp "$address_book"
        echo "Record deleted successfully."
    else
        echo "Record not found."
    fi
}

modify() {
    echo "Enter name, phone, or email of the record to modify: "
    read values

    if grep -q "$values" "$address_book"; then
        grep -v "$values" "$address_book" > temp && mv temp "$address_book"

        echo "Enter new details for $values"
        echo "Enter Name:"
        read name
        echo "Enter Phone Number:"
        read phone
        echo "Enter Email:"
        read email

        echo "$name | $phone | $email" >> "$address_book"
        echo "Record updated."
    else
        echo "Record not found."
    fi
}

while true; do
  echo "Choose an option:"
  echo "a) Create address book"
  echo "b) View address book"
  echo "c) Insert a record"
  echo "d) Delete a record"
  echo "e) Modify a record"
  echo "f) Exit"
  read -p "Option: " choice

  case $choice in
    a) create ;;
    b) view ;;
    c) insert ;;
    d) delete ;;
    e) modify ;;
    f) echo "Exiting."; break ;;
    *) echo "Invalid option." ;;
  esac
done
