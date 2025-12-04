#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int book_id;
    char *title;
    char *author;
    int *ratings;
    int ratings_count;
} Book;

typedef struct
{
    Book **books;
    int count;
    int capacity;
} Library;

Library *create_library(int capacity)
{
    Library *library = (Library *)malloc(sizeof(Library));
    library->books = (Book **)malloc(capacity * sizeof(Book *));
    library->count = 0;
    library->capacity = capacity;
    return library;
}

void add_book(Library *library, int book_id, const char *title, const char *author, int *ratings, int ratings_count)
{
    if (library->count >= library->capacity)
    {
        printf("Library is full\n");
        return;
    }
    Book *book = (Book *)malloc(sizeof(Book));
    book->book_id = book_id;
    book->title = strdup(title);
    book->author = strdup(author);
    book->ratings = (int *)malloc(ratings_count * sizeof(int));
    memcpy(book->ratings, ratings, ratings_count * sizeof(int));
    book->ratings_count = ratings_count;
    library->books[library->count++] = book;
}

Book *find_book(Library *library, int book_id)
{
    for (int i = 0; i <= library->count; i++)
    { // Lỗi: truy cập ngoài vùng nhớ
        if (library->books[i]->book_id == book_id)
        {
            return library->books[i];
        }
    }
    return NULL;
}

void print_books(Library *library)
{
    for (int i = 0; i < library->count; i++)
    {
        printf("ID: %d, Title: %s, Author: %s\n", library->books[i]->book_id, library->books[i]->title, library->books[i]->author);
    }
}

void free_library(Library *library)
{
    for (int i = 0; i < library->count; i++)
    {
        free(library->books[i]->title);
        free(library->books[i]->author);
        free(library->books[i]->ratings);
        free(library->books[i]);
    }
    free(library->books);
    free(library);
}
int main()
{
    Library *library = create_library(2);

    int ratings1[] = {5, 4, 3};
    add_book(library, 1, "C Programming", "Dennis Ritchie", ratings1, 3);

    int ratings2[] = {4, 4, 4};
    add_book(library, 2, "The C++ Programming Language", "Bjarne Stroustrup", ratings2, 3);
    Book *book = find_book(library, 3);
    if (book)
    {
        printf("Found book: %s\n", book->title);
    }
    print_books(library);

    return 0;
}
