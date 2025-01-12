# CLI E-commerce Recommender

Welcome to the **CLI E-commerce Recommender**, a robust command-line application designed to mimic the functionality of an online e-commerce platform while providing intelligent recommendations to users. This project is a college project developed for the **DSC (Data Structures)** course.

## Project Features

### Key Functionalities
1. **Sequential Pattern Mining**: 
   - The recommendation system leverages sequential pattern mining techniques to analyze user purchase patterns and suggest relevant products.
2. **Search with Hashmaps**: 
   - Optimized product asearches using hashmaps 
3. **E-commerce Features**:
   - Product search.
   - Add items to cart and wishlist.
   - Place and manage orders.
4. **User Interaction via CLI**:
   - Intuitive and user-friendly command-line interface to facilitate seamless navigation and operations.

### File Structure

```plaintext
.
├── LICENSE                    
├── README.md                  
├── cart.c                     
├── cli.c                      
├── data.csv                   
├── generated_orders.txt       .
├── list.c                     
├── main.c                     
├── recommender.c              
├── shared.h                   
├── wishlist.c                 
```

### Tech Stack
- **Language**: C
- **Algorithms**: Sequential Pattern Mining, Hashmap-based optimizations,weighted probabilities
- **File Handling**: Persistent data storage using `.csv` and `.txt` files.

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/swanand11/cli-ecommerce-recommender.git
   ```

2. Compile the project using GCC:
   ```bash
   gcc -o program main.c cart.c cli.c list.c recommender.c wishlist.c
   ```

3. Run the application:
   ```bash
   ./program
   ```

4. Follow the on-screen instructions to navigate the CLI and explore features like product search, adding to cart/wishlist, and viewing recommendations.

## Collaborators

This project was collaboratively developed by the following team members:

1. **Swanand Gadwe**
2. **Shrihari Joshi**
3. **Swaroop Kalli**
4. **Shubham Khatri**

## License

This project is licensed under the [MIT License](LICENSE).

## Future Enhancements

- Integration of more advanced machine learning algorithms for recommendations.
- GUI implementation for a more user-friendly experience.
- Database integration for scalable and dynamic data management.

---

We hope you enjoy exploring our CLI E-commerce Recommender project. Happy shopping!
