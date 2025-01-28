M = [ 1 1 1; 1 0 1; -1 0 0 ];

% Calculate the determinant
determinant = det(M);

% Define a function to calculate the cofactor of a matrix element
function cofactor = calculateCofactor(M, i, j)
    % Extract the submatrix excluding the i-th row and j-th column
    subMatrix = M([1:i-1, i+1:end], [1:j-1, j+1:end]);
    % Calculate the determinant of the submatrix
    subMatrixDeterminant = det(subMatrix);
    % Determine the sign based on the position of the element
    cofactor = (-1)^(i+j) * subMatrixDeterminant;
end

% Calculate the cofactor matrix
C = zeros(size(M));
for i = 1:size(M, 1)
    for j = 1:size(M, 2)
        C(i, j) = calculateCofactor(M, i, j);
    end
end

% Calculate the inverse using matrix division
inverseM = C / determinant;

% Display the inverse matrix
disp(inverseM);